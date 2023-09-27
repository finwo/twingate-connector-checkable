#!/usr/bin/env bash

for tag in $(cat tags); do
  tag=${tag} envsubst < Dockerfile.tmpl > Dockerfile
  # docker build -t finwo/twingate-connector-checkable:${tag} .
  docker build -t finwo/twingate-connector-checkable:${tag} --push .
done

