# Log

## Ryzen 9 something
### tl;dr
- took ~20 minutes
- `imposm import -connection postgis://postgres:postgres@localhost/gis -mapping mappings/imposm.json -deployproduction -read maps/germany-latest.osm.pbf -write`
### imposm output
```shell
nbdy@c0:~/CLionProjects/carpi$ imposm import -connection postgis://postgres:postgres@localhost/gis -mapping mappings/imposm.json -deployproduction -read maps/germany-latest.osm.pbf -write
[2021-10-11T22:05:50+02:00] 0:00:00 [step] Starting: Imposm
[2021-10-11T22:05:50+02:00] 0:00:00 [step] Starting: Reading OSM data
[2021-10-11T22:05:50+02:00] 0:00:00 [info] reading maps/germany-latest.osm.pbf with data till 2021-10-09 22:21:28 +0200 CEST
[2021-10-11T22:06:50+02:00] 0:01:00 [progress]   1m0s C: 1907000/s (114432000) N:   37100/s (2229320) W:       0/s (0) R:      0/s (0)
[2021-10-11T22:07:50+02:00] 0:02:00 [progress]   2m0s C: 2602000/s (312192000) N:   49200/s (5912529) W:       0/s (0) R:      0/s (0)
[2021-10-11T22:08:39+02:00] 0:02:49 [progress]  2m49s C: 2916000/s (349953025) N:   55800/s (6701417) W:       0/s (57145484) R:      0/s (524106)
[2021-10-11T22:08:39+02:00] 0:02:49 [step] Finished: Reading OSM data in 2m49.26392902s
[2021-10-11T22:08:39+02:00] 0:02:49 [step] Starting: Importing OSM data
[2021-10-11T22:08:39+02:00] 0:02:49 [step] Starting: Writing OSM data
[2021-10-11T22:09:39+02:00] 0:03:49 [progress]   1m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:       0/s ( 0.0%) R:    520/s ( 5.9%)
[2021-10-11T22:10:39+02:00] 0:04:49 [progress]   2m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:       0/s ( 0.0%) R:    940/s (21.5%)
[2021-10-11T22:11:39+02:00] 0:05:49 [progress]   3m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:       0/s ( 0.0%) R:   1200/s (41.2%)
[2021-10-11T22:12:39+02:00] 0:06:49 [progress]   4m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:       0/s ( 0.0%) R:   1560/s (71.4%)
[2021-10-11T22:13:39+02:00] 0:07:49 [progress]   5m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   26200/s ( 0.0%) R:   1750/s (100.0%)
[2021-10-11T22:14:39+02:00] 0:08:49 [progress]   6m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   33000/s ( 3.5%) R:   1750/s (100.0%)
[2021-10-11T22:15:39+02:00] 0:09:49 [progress]   7m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   40300/s ( 8.5%) R:   1750/s (100.0%)
[2021-10-11T22:16:39+02:00] 0:10:49 [progress]   8m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   48200/s (15.2%) R:   1750/s (100.0%)
[2021-10-11T22:17:39+02:00] 0:11:49 [progress]   9m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   55000/s (23.1%) R:   1750/s (100.0%)
[2021-10-11T22:18:39+02:00] 0:12:49 [progress]  10m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   61900/s (32.6%) R:   1750/s (100.0%)
[2021-10-11T22:19:39+02:00] 0:13:49 [progress]  11m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   68500/s (43.2%) R:   1750/s (100.0%)
[2021-10-11T22:20:39+02:00] 0:14:49 [progress]  12m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   74700/s (55.0%) R:   1750/s (100.0%)
[2021-10-11T22:21:39+02:00] 0:15:49 [progress]  13m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   79300/s (66.7%) R:   1750/s (100.0%)
[2021-10-11T22:22:39+02:00] 0:16:49 [progress]  14m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   82000/s (77.5%) R:   1750/s (100.0%)
[2021-10-11T22:23:39+02:00] 0:17:49 [progress]  15m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   83500/s (87.8%) R:   1750/s (100.0%)
[2021-10-11T22:24:39+02:00] 0:18:49 [progress]  16m0s C:       0/s ( 0.0%) N:       0/s ( 0.0%) W:   85000/s (98.2%) R:   1750/s (100.0%)
[2021-10-11T22:25:08+02:00] 0:19:17 [step] Finished: Writing OSM data in 16m28.488334639s
[2021-10-11T22:25:08+02:00] 0:19:17 [step] Starting: Creating generalized tables
[2021-10-11T22:25:08+02:00] 0:19:17 [step] Starting: Generalizing osm_waterways into osm_waterways_gen1
[2021-10-11T22:25:08+02:00] 0:19:17 [progress] 16m28s C:       0/s ( 0.0%) N:       0/s (100.0%) W:   86500/s (100.0%) R:   1750/s (100.0%)
[2021-10-11T22:25:08+02:00] 0:19:17 [step] Starting: Generalizing osm_waterareas into osm_waterareas_gen1
[2021-10-11T22:25:08+02:00] 0:19:17 [step] Starting: Generalizing osm_roads into osm_roads_gen1
[2021-10-11T22:25:08+02:00] 0:19:17 [step] Starting: Generalizing osm_landusages into osm_landusages_gen1
[2021-10-11T22:25:10+02:00] 0:19:20 [step] Finished: Generalizing osm_waterareas into osm_waterareas_gen1 in 2.366651219s
[2021-10-11T22:25:17+02:00] 0:19:27 [step] Finished: Generalizing osm_waterways into osm_waterways_gen1 in 9.46711877s
[2021-10-11T22:25:24+02:00] 0:19:33 [step] Finished: Generalizing osm_roads into osm_roads_gen1 in 16.03515162s
[2021-10-11T22:25:49+02:00] 0:19:58 [step] Finished: Generalizing osm_landusages into osm_landusages_gen1 in 40.853639501s
[2021-10-11T22:25:49+02:00] 0:19:58 [step] Starting: Generalizing osm_landusages into osm_landusages_gen0
[2021-10-11T22:25:49+02:00] 0:19:58 [step] Starting: Generalizing osm_waterways into osm_waterways_gen0
[2021-10-11T22:25:49+02:00] 0:19:58 [step] Starting: Generalizing osm_roads into osm_roads_gen0
[2021-10-11T22:25:49+02:00] 0:19:58 [step] Starting: Generalizing osm_waterareas into osm_waterareas_gen0
[2021-10-11T22:25:49+02:00] 0:19:58 [step] Finished: Generalizing osm_waterareas into osm_waterareas_gen0 in 184.050148ms
[2021-10-11T22:25:59+02:00] 0:20:09 [step] Finished: Generalizing osm_waterways into osm_waterways_gen0 in 10.687842772s
[2021-10-11T22:26:00+02:00] 0:20:09 [step] Finished: Generalizing osm_roads into osm_roads_gen0 in 11.014026989s
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Generalizing osm_landusages into osm_landusages_gen0 in 12.901190463s
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating generalized tables in 53.755065904s
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry indices
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_places
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_landusages_gen1
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_landusages_gen0
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_landusages
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_transport_areas
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_barrierways
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_waterareas_gen0
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_housenumbers_interpolated
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_waterareas_gen1
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_roads
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_roads_gen0
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_waterways_gen0
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_transport_points
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_barrierpoints
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_roads_gen1
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating OSM id index on osm_waterways_gen1
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_admin
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_waterways
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_waterareas
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_buildings
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_housenumbers
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_aeroways
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_amenities
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating OSM id index on osm_waterareas_gen0 in 14.863517ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_waterareas_gen0
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_waterareas_gen0 in 18.506349ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating OSM id index on osm_waterareas_gen1 in 34.403209ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_waterareas_gen1
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_aeroways in 50.061231ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_housenumbers_interpolated in 59.505783ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_transport_areas in 121.319662ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_waterareas_gen1 in 129.57981ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating OSM id index on osm_landusages_gen0 in 231.890665ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Starting: Creating geometry index on osm_landusages_gen0
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_amenities in 307.071022ms
[2021-10-11T22:26:02+02:00] 0:20:11 [step] Finished: Creating geometry index on osm_admin in 351.582123ms
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Finished: Creating OSM id index on osm_waterways_gen1 in 921.65425ms
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Starting: Creating geometry index on osm_waterways_gen1
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Finished: Creating OSM id index on osm_waterways_gen0 in 1.130532047s
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Starting: Creating geometry index on osm_waterways_gen0
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Finished: Creating geometry index on osm_places in 1.149167008s
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Finished: Creating OSM id index on osm_roads_gen1 in 1.298716544s
[2021-10-11T22:26:03+02:00] 0:20:12 [step] Starting: Creating geometry index on osm_roads_gen1
[2021-10-11T22:26:03+02:00] 0:20:13 [step] Finished: Creating OSM id index on osm_landusages_gen1 in 1.500881719s
[2021-10-11T22:26:03+02:00] 0:20:13 [step] Starting: Creating geometry index on osm_landusages_gen1
[2021-10-11T22:26:03+02:00] 0:20:13 [step] Finished: Creating OSM id index on osm_roads_gen0 in 1.501494775s
[2021-10-11T22:26:03+02:00] 0:20:13 [step] Starting: Creating geometry index on osm_roads_gen0
[2021-10-11T22:26:03+02:00] 0:20:13 [step] Finished: Creating geometry index on osm_landusages_gen0 in 1.544739548s
[2021-10-11T22:26:05+02:00] 0:20:14 [step] Finished: Creating geometry index on osm_waterareas in 2.892792738s
[2021-10-11T22:26:06+02:00] 0:20:15 [step] Finished: Creating geometry index on osm_barrierpoints in 4.172790645s
[2021-10-11T22:26:06+02:00] 0:20:15 [step] Finished: Creating geometry index on osm_transport_points in 4.295372409s
[2021-10-11T22:26:07+02:00] 0:20:17 [step] Finished: Creating geometry index on osm_barrierways in 5.623348972s
[2021-10-11T22:26:12+02:00] 0:20:22 [step] Finished: Creating geometry index on osm_waterways in 10.575007712s
[2021-10-11T22:26:13+02:00] 0:20:23 [step] Finished: Creating geometry index on osm_waterways_gen0 in 10.57158998s
[2021-10-11T22:26:16+02:00] 0:20:25 [step] Finished: Creating geometry index on osm_waterways_gen1 in 13.326545399s
[2021-10-11T22:26:19+02:00] 0:20:28 [step] Finished: Creating geometry index on osm_landusages_gen1 in 15.939360426s
[2021-10-11T22:26:22+02:00] 0:20:31 [step] Finished: Creating geometry index on osm_roads_gen1 in 18.989212395s
[2021-10-11T22:26:22+02:00] 0:20:32 [step] Finished: Creating geometry index on osm_roads_gen0 in 19.041962615s
[2021-10-11T22:26:40+02:00] 0:20:50 [step] Finished: Creating geometry index on osm_housenumbers in 38.541820452s
[2021-10-11T22:27:04+02:00] 0:21:13 [step] Finished: Creating geometry index on osm_landusages in 1m1.994928375s
[2021-10-11T22:28:17+02:00] 0:22:27 [step] Finished: Creating geometry index on osm_roads in 2m15.532022433s
[2021-10-11T22:31:23+02:00] 0:25:32 [step] Finished: Creating geometry index on osm_buildings in 5m20.839262525s
[2021-10-11T22:31:23+02:00] 0:25:32 [step] Finished: Creating geometry indices in 5m20.839436801s
[2021-10-11T22:31:23+02:00] 0:25:32 [step] Finished: Importing OSM data in 22m43.082934357s
[2021-10-11T22:31:23+02:00] 0:25:32 [step] Starting: Rotating tables
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_waterareas from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_buildings from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_transport_areas from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_transport_points from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_places from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_housenumbers_interpolated from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_barrierways from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_amenities from import -> public -> backup
[2021-10-11T22:31:23+02:00] 0:25:32 [info] Rotating osm_roads from import -> public -> backup
[2021-10-11T22:31:24+02:00] 0:25:33 [info] Rotating osm_waterways from import -> public -> backup
[2021-10-11T22:31:24+02:00] 0:25:33 [info] Rotating osm_landusages from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_housenumbers from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_aeroways from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_barrierpoints from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_admin from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_roads_gen0 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_roads_gen1 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_waterways_gen0 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_waterways_gen1 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_landusages_gen1 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_landusages_gen0 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_waterareas_gen1 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [info] Rotating osm_waterareas_gen0 from import -> public -> backup
[2021-10-11T22:31:25+02:00] 0:25:34 [step] Finished: Rotating tables in 2.058268981s
[2021-10-11T22:31:25+02:00] 0:25:34 [step] Finished: Imposm in 25m34.405234539s
```