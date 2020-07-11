#!/bin/bash

PASSWORD=${1:-"postgres"}
PGFILE=${2:-"__NONE__"}
echo "the new postgres password will be '$PASSWORD'"
if [ "$PGFILE" != "__NONE__" ]; then
  echo "you need to specify a file to import"
  echo "./postgis.sh {postgres_password} {file_to_import}"
  echo "eg.: ./postgis.sh postgres germany.osm.pbf"
  exit 1
fi

sudo -u postgres psql -U postgres -d postgres -c "alter user postgres with password '$PASSWORD';"
sudo -u postgres createdb gis
sudo -u postgres psql -d gis -c 'CREATE EXTENSION postgis; CREATE EXTENSION hstore;'

if [ ! -d "imposm" ]; then
  echo "downloading and unpacking imposm"
  wget https://github.com/omniscale/imposm3/releases/download/v0.10.0/imposm-0.10.0-linux-x86-64.tar.gz
  tar xf imposm-0.10.0-linux-x86-64.tar.gz
  mv imposm-0.10.0-linux-x86-64/ imposm
  rm imposm-0.10.0-linux-x86-64.tar.gz
fi

echo "importing. this will take quiet a while. you can even make a proper nap."
imposm --read --write --optimize -h localhost -p 5432 -U postgres -d gis "$PGFILE"