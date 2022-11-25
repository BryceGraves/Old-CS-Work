#!/bin/bash

START_VAL=
END_VAL=
VERBOSE=0
TOCHECK=

function show_help() {
  echo "Thar be no help!"
  echo "Todays date is `date`"
  exit
}

function verbose_start_values() {
  echo "Start value: ${START_VAL} and End value: ${END_VAL}"
}

while getopts "hvs:e:" OPT
do
  case "${OPT}" in
    h)
      show_help
      ;;
    v)
      VERBOSE=1
      ;;
    s)
      START_VAL=${OPTARG}
      ;;
    e)
      END_VAL=${OPTARG}
      ;;
    *)
      echo "Unknown command line option ${OPTARG}"
      ;;
    esac
done


if [ -z ${START_VAL} ]
then
  if [ -z ${END_VAL} ]
  then
    show_help
    exit
  fi
  START_VAL=1
elif [ -z ${END_VAL} ]
then
  END_VAL=10
fi

if [ ${VERBOSE} = 1 ]
then
  verbose_start_values
fi

for (( c=$START_VAL; c<=$END_VAL; c++))
do
  $path_of_prog./foo $c
  TOCHECK=${?}
  if [ ${TOCHECK} = 0 ]
  then
    echo "${c} was successful"
  elif [ ${TOCHECK} = 1 ]
  then
    if [ ${VERBOSE} = 1 ]
    then
      echo "${c} returned 1"
    fi
  elif [ ${TOCHECK} = 2 ]
  then
    if [ ${VERBOSE} = 1 ]
    then
      echo "${c} returned 2"
    fi
  elif [ ${TOCHECK} = 3 ]
  then
    if [ ${VERBOSE} = 1 ]
    then
      echo "${c} returned 3"
    fi
  fi

done
