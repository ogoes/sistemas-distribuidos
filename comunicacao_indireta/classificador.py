import json
import pika

from pprint import pprint


def callback(ch, method, properties, body):
    info = json.loads(body)

    ch.exchange_declare(exchange="tweets", exchange_type="topic")

    for tags in info["hashtags"]:
        ch.basic_publish(exchange="tweets", routing_key=tags, body=info["text"])


with pika.BlockingConnection(pika.ConnectionParameters(host="localhost")) as connection:
    channel = connection.channel()

    channel.queue_declare(queue="tweets", durable=True)

    channel.basic_consume(queue="tweets", auto_ack=True, on_message_callback=callback)

    channel.start_consuming()

