import pika
import sys


def callback(ch, method, properties, body):
    print("Content:", str(body))


with pika.BlockingConnection(pika.ConnectionParameters(host="localhost")) as connection:
    channel = connection.channel()
    channel.exchange_declare(exchange='tweets', exchange_type='topic')

    result = channel.queue_declare('', exclusive=True)
    queue_name = result.method.queue

    binding_keys = sys.argv[1:]

    for binding_key in binding_keys:
        channel.queue_bind(
            exchange='tweets', queue=queue_name, routing_key=binding_key)

    channel.basic_consume(
        queue=queue_name, on_message_callback=callback, auto_ack=True)

    channel.start_consuming()

