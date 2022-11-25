import React from 'react';

import { Segment, Header } from 'semantic-ui-react';

import ArtistList from '../containers/ArtistList';

/**
 * TODO: describe what params this component needs and what it does
 */
const GenreSection = ({ genre, artists }) => {
  if (!genre) {
    return (
      <Segment>
        <Header>Album Name Loading</Header>
      </Segment>
    );
  }

  return (
    <Segment>
      <Header textAlign="center">{genre}</Header>
      <ArtistList artists={artists}></ArtistList>
    </Segment>
  );
};

export default GenreSection;
