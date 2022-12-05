#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"

CONTAINER=registry.gitlab.steamos.cloud/steamrt/sniper/sdk
CONTAINER_NAME=sdk-builder

function startContainer {
	if [ -z "$(docker ps | grep $CONTAINER_NAME)" ]; then
		echo "Started.."
		docker run --rm -it -d -v "$PWD/../":"$PWD/../" --user "$(id -u):$(id -g)" -w "$PWD" --name "$CONTAINER_NAME" $CONTAINER bash
	fi
}

startContainer

docker exec -w "$PWD" -e "GCC_VER=-9" -e "CLICOLOR_FORCE=1" -e "COLORTERM=$COLORTERM" -e "TERM=$TERM" -e "CCACHE_DIR=.ccache" "$CONTAINER_NAME" "$@"

