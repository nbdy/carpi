#!/bin/bash

PGUSER="postgres"
PGPASS="postgres"
PGHOST="localhost"
PGDB="gis"
MAPPING="mappings/imposm.json"
INPUT="maps/germany-latest.osm.pbf"

if [ -x "$(command -v imposm)" ]; then
  if [ -x "$(command -v go)" ]; then
    sudo apt install -y golang libleveldb-dev libgeos-dev postgis postgresql
  fi

  go get github.com/omniscale/imposm3
  go install github.com/omniscale/imposm3/cmd/imposm
  echo "export GOPATH=$HOME/go" >> ~/.bashrc
  echo "export PATH=$PATH:$GOPATH/bin" >> ~/.bashrc
  source ~/.bashrc
fi

sudo -u postgres createdb gis
sudo -u postgres psql -d gis -c 'CREATE EXTENSION postgis; CREATE EXTENSION hstore;'

imposm import -connection postgis://$PGUSER:$PGPASS@$PGHOST/$PGPASS -mapping $MAPPING -deployproduction -read $INPUT -write