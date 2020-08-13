import io.eberlein.disqt 1.0
import io.eberlein.rsettingsqt 1.0


RSettings {
    id: rsettings
    redis: Redis {
        id: redis
        host: "127.0.0.1"
        port: 6379

        onSubscriberIsConnectedChanged: subscriberConnectedChanged()
        onClientIsConnectedChanged: clientConnectedChanged()
    }

    signal subscriberConnectedChanged
    signal clientConnectedChanged

    onReady: {
        console.log("connecting to redis server")
        redis.connect()
        console.log("connected to redis server")
    }
}
