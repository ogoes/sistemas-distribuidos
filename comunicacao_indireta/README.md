# Comunicação indireta


## Ferramentas
  [Python 3.7](https://www.python.org)
  [RabbitMQ](https://www.rabbitmq.com)
  [Pika](https://pika.readthedocs.io/en/stable/)
  [Tweepy](https://www.tweepy.org)


## Variáveis de ambiente

    TWITTER_API_KEY

    TWITTER_API_KEY_SECRET

    TWITTER_ACCESS_TOKEN

    TWITTER_ACCESS_TOKEN_SECRET

## Daemons

    ```sh
      # systemctl start rabbitmq
    ```

## Como usar

  ### coletor
   - busca por tweets que contenham algum dos tracks passados
  ```sh
    $ python3 coletor.py track1 track2 track3 ...
  ```

  ### classificador
  ```sh
    $ python3 classificador.py
  ```


  ### assinante
   - mostra tweets com as hashtags passadas

  ```sh
    $ python3 assinante.py hashtags1 hashtags2 ...
  ```




