import pika

import sys
import os
import tweepy
import json


auth = tweepy.OAuthHandler(
    os.environ.get('TWITTER_API_KEY'),
    os.environ.get('TWITTER_API_KEY_SECRET')
)
auth.set_access_token(
    os.environ.get('TWITTER_ACCESS_TOKEN'),
    os.environ.get('TWITTER_ACCESS_TOKEN_SECRET')
)
api = tweepy.API(auth)


with pika.BlockingConnection(
    parameters=pika.ConnectionParameters(host="localhost")
) as connection:

    channel = connection.channel()
    channel.queue_declare(queue="tweets", durable=True)

    class MyStreamListener(tweepy.StreamListener):
        def on_status(self, status):

            message = json.dumps(
                {
                    "hashtags": [
                        tags["text"] for tags in status._json["entities"]["hashtags"]
                    ],
                    "text": status.text,
                }
            )
            channel.basic_publish(exchange="", routing_key="tweets", body=message)


    myStreamListener = MyStreamListener()
    myStream = tweepy.Stream(auth=api.auth, listener=myStreamListener)

    myStream.filter(track=sys.argv[1:])



