import React from 'react';

import { Header, Message } from 'semantic-ui-react';

import CategorySection from './CategorySection';

/**
 * TODO: describe what params this component needs and what it does
 */
const CategoryList = ({ categories }) => {
  const categoryKeys = Object.keys(categories);

  if (categoryKeys === 0) {
    return (
      <>
        <Header>No Categories Created</Header>
        <Message>Please create a category</Message>
      </>
    );
  }

  const content = categoryKeys.map((categoryKey) => {
    return <CategorySection category={categories[categoryKey]} categoryId={categoryKey} />;
  });

  return <>{content}</>;
};

export default CategoryList;
