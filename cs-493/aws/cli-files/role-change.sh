#!/bin/bash
if [ "$1" == "admin" ]; then
  echo "Using admin!"
  echo "This user does not care for permissions"

  cat admin_config > config
  cat admin_credentials > credentials
elif [ "$1" == "bryce" ]; then
  echo "Using bryce!"
  echo "This user has bryce role which gives full s3 access"

  cat bryce_config > config
  cat bryce_credentials > credentials
elif [ "$1" == "poverty" ]; then
  echo "Using poverty boi!"
  echo "This is the user poverty-boi which has the contractors role attached to it"

  cat poverty_boi_config > config
  cat poverty_boi_credentials > credentials
elif [ "$1" == "very-poverty" ]; then
  echo "Using very poverty boi!"
  echo "This is the user poverty-boi which has no role attached to it"

  cat very_poverty_boi_config > config
  cat very_poverty_boi_credentials > credentials
else
  echo "use admin, bryce, poverty, or very-poverty"
fi