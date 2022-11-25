import React from 'react';

import { Segment, Header } from 'semantic-ui-react';

import AlbumList from '../containers/AlbumList';

/**
 * TODO: describe what params this component needs and what it does
 */
const ArtistSection = ({ artist, albums }) => {
  if (!artist) {
    return (
      <Segment>
        <Header>Album Name Loading</Header>
      </Segment>
    );
  }

  return (
    <Segment>
      <Header textAlign="center">{artist}</Header>
      <AlbumList albums={albums}></AlbumList>
    </Segment>
  );
};

export default ArtistSection;
