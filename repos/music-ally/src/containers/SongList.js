import React from 'react';
import { useDispatch } from 'react-redux';

import { setSong } from '../actions';

import { Button, Header, Message } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const SongList = ({ songs }) => {
  const dispatch = useDispatch();

  if (songs.length === 0) {
    return (
      <>
        <Header>No Songs Uploaded</Header>
        <Message>Please upload a song</Message>
      </>
    );
  }

  console.log(songs);

  const handleSetSong = (song) => {
    dispatch(setSong(song));
  };

  const colorOptions = [
    'red',
    'orange',
    'yellow',
    'olive',
    'green',
    'teal',
    'blue',
    'violet',
    'purple',
    'pink',
    'brown',
    'grey',
    'black',
  ];

  const colorOptionsCount = colorOptions.length;

  const list = songs.map((song, index) => {
    return (
      <Button
        color={colorOptions[index % colorOptionsCount]}
        fluid
        onClick={(_) => handleSetSong(song)}
      >
        {song.name || 'Blank Title'}
      </Button>
    );
  });

  return (
    <Button.Group className="mb-3" fluid vertical>
      {list}
    </Button.Group>
  );
};

export default SongList;
