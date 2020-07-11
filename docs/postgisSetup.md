## postgis setup

#### prerequisites:
- postgresql & postgis
- [imposm](https://github.com/omniscale/imposm3)
- [data](https://download.geofabrik.de/) to import

#### why imposm?
- [does not fill ram up like osm2pgsql does](https://github.com/smthnspcl/carpi/blob/master/docs/notes.md)

#### there is a script now
```shell script
./postgis.sh postgres osm_files/europe-latest.osm.pbf
```

#### setup:
the import will take quiet a while on an rpi (3b+)
```
sudo -u postgres createdb gis
sudo -u postgres psql -d gis -c 'CREATE EXTENSION postgis; CREATE EXTENSION hstore;'

# should be executed in screen or tmux session
# takes ~8 hours with a 500 MB file
# takes ~49 hours with a 3GB file

imposm --read --write --optimize -h localhost -p 5432 -U postgres -d gis [file]
[18:51:46] ## reading bayern-latest.osm.pbf
[18:51:46] coords: 41753k nodes: 835k ways: 5964k relations: 41k (estimated)
[19:41:30] coords: 54576k nodes: 188k ways: 8067k relations: 33k
[19:41:33] reading took 49m 48s
...
[21:04:00] ## dropping/creating tables
[21:04:01] ## writing data
[21:19:26] relations: 34k/34k
[21:20:24] relations: total time 16m 23s for 34047 (34/s)
[03:51:29] ways: 8067k/8067k
[03:51:42] ways: total time 6 h 31m 18s for 8067107 (343/s)
[03:56:26] nodes: 188k/188k
[03:56:32] nodes: total time 4 m 49s for 188799 (651/s)
[03:56:33] ## creating generalized tables
[04:08:59] generalizing tables took 12m 26s
[04:08:59] ## creating union views
[04:08:59] creating views took 0 s
[04:08:59] ## creating geometry indexes
[04:31:09] creating indexes took 22m 9 s
[04:31:09] ## post-processing tables
[04:34:36] post-processing tables took 3 m 27s
[04:34:36] writing took 7 h 30m 36s
[04:34:37] ## optimizing tables
...
[05:15:22] optimizing took 40m 44s
[05:15:22] imposm took 8 h 11m 22s
```
on my pc:
```
[21:36:08] imposm took 22m 51s
```
with 2.8gb germany.pbf
```
[03:39:01] relations: 207k/207k
[03:40:06] relations: total time 1 h 19m 0 s for 207743 (43/s)
[10:08:32] ways: 48530k/48530k
[10:08:44] ways: total time 30h 28m 37s for 48530746 (442/s)
[10:28:28] nodes: 1162k/1162k
[10:28:33] nodes: total time 19m 48s for 1162495 (978/s)
[10:28:33] ## creating generalized tables
[11:30:12] generalizing tables took 1 h 1 m 39s
[11:30:12] ## creating union views
[11:30:13] creating views took 0 s
[11:30:13] ## creating geometry indexes
[15:12:28] creating indexes took 3 h 42m 15s
[15:12:28] ## post-processing tables
[15:46:46] post-processing tables took 34m 18s
[15:46:46] writing took 37h 25m 41s
[22:24:48] imposm took 48h 40m 53s
```
again with 2.8gb germany.pbf and --merge-cache
```
[06:15:03] relations: 207k/207k
[06:16:47] relations: total time 2 h 4 m 56s for 207743 (27/s)
[05:45:51] ways: 48530k/48530k
[05:46:07] ways: total time 47h 29m 20s for 48530746 (283/s)
[06:15:27] nodes: 1162k/1162k
[06:15:34] nodes: total time 29m 26s for 1162495 (657/s)
[07:22:02] ## creating geometry indexes
[11:44:34] creating indexes took 4 h 22m 31s
[11:44:34] ## post-processing tables
[12:20:53] post-processing tables took 36m 19s
[12:20:53] writing took 56h 9 m 5 s
[19:26:41] optimizing took 7 h 5 m 46s
[19:26:41] imposm took 73h 26m 4 s
[12:20:53] writing took 56h 9 m 5 s
```
