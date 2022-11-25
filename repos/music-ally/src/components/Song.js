import React, { useEffect, useState } from 'react';

import AudioPlayer from 'react-h5-audio-player';
import 'react-h5-audio-player/lib/styles.css';

import { Header, Message, Segment } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const SongPlayer = ({ song }) => {
  if (!song.name) {
    return (
      <>
        <Header>No Song Selected</Header>
        <Message>Please select a song</Message>
      </>
    );
  }

  return (
    <>
      <Segment>
        <AudioPlayer
          autoPlay
          className="mb-3"
          src={song.url}
          onPlay={(e) => console.log('onPlay')}
        />
      </Segment>
    </>
  );
};

export default SongPlayer;
