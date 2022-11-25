import React from 'react';

import { Segment, Header } from 'semantic-ui-react';

import SongList from '../containers/SongList';

/**
 * TODO: describe what params this component needs and what it does
 */
const AlbumSection = ({ album, songs }) => {
  if (!album) {
    return (
      <Segment>
        <Header>Album Name Loading</Header>
      </Segment>
    );
  }

  return (
    <Segment>
      <Header textAlign="center">{album}</Header>
      <SongList songs={songs} />
    </Segment>
  );
};

export default AlbumSection;
