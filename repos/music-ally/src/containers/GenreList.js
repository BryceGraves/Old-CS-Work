import React from 'react';

import { Header, Message } from 'semantic-ui-react';

import GenreSection from '../components/GenreSection';

/**
 * TODO: describe what params this component needs and what it does
 */
const GenreList = ({ genres }) => {
  const genreKeys = Object.keys(genres || {});

  if (genreKeys.length === 0) {
    return (
      <>
        <Header textAlign="center">No Genres To Display</Header>
        <Message>Please upload a song</Message>
      </>
    );
  }

  const content = genreKeys.map((genreKey) => {
    return <GenreSection genre={genreKey} artists={genres[genreKey]} />;
  });

  return <>{content}</>;
};

export default GenreList;
