import React from 'react';

import { Header, Message } from 'semantic-ui-react';

import AlbumSection from '../components/AlbumSection';

/**
 * TODO: describe what params this component needs and what it does
 */
const AlbumList = ({ albums }) => {
  const albumKeys = Object.keys(albums || {});

  if (albumKeys.length === 0) {
    return (
      <>
        <Header textAlign="center">No Albums To Display</Header>
        <Message>Please upload a song</Message>
      </>
    );
  }

  const content = albumKeys.map((albumKey) => {
    return <AlbumSection album={albumKey} songs={albums[albumKey]} />;
  });

  return <>{content}</>;
};

export default AlbumList;
