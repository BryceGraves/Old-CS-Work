import React from 'react';

import { Header, Message } from 'semantic-ui-react';

import ArtistSection from '../components/ArtistSection';

/**
 * TODO: describe what params this component needs and what it does
 */
const ArtistList = ({ artists }) => {
  const artistKeys = Object.keys(artists || {});

  if (artistKeys.length === 0) {
    return (
      <>
        <Header textAlign="center">No Artists To Display</Header>
        <Message>Please upload a song</Message>
      </>
    );
  }

  const content = artistKeys.map((artistKey) => {
    return <ArtistSection artist={artistKey} albums={artists[artistKey]} />;
  });

  return <>{content}</>;
};

export default ArtistList;
