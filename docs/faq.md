## faq:
- Q: how to setup a postgis database on the raspberry pi?
- A: [postgisSetup](https://github.com/smthnspcl/carpi/blob/master/docs/postgisSetup.md)

+ Q: are there cases which i can 3d print?<br>
+ A: yah.. [cadpi](https://github.com/smthnspcl/cadpi)<br>

- Q: can i have the ui be there upon powering on?<br>
- A: sure, add 'carpi &' before the 'exit 0' in '/etc/rc.local'<br>

+ Q: audio is not playing on raspberry pi<br>
+ A: (in my case):
<br>

```
# to find the audio device you want to use
$ aplay -l
# ... snip ...
card 1: Audio [USB Audio], device 0: USB Audio [USB Audio]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
  
# card 1; device 0 -> hw:1,0

# (if starting via /etc/rc.local this must be in /root/)
$ vim ~/.asoundrc
pcm.!default {
  type asym
   playback.pcm {
     type plug
     slave.pcm "hw:1,0"
   }
}
```