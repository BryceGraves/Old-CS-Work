/**
 * TODO: add description of this
 */
export const extractAndStoreData = (userCategoryRef, userCategories, notesDataFetch) => (
  dispatch
) => {
  console.log('Extracting Notes Data');
  Promise.all(
    userCategories.docs.map((category) => {
      return userCategoryRef
        .doc(category.id)
        .collection('notes')
        .get()
        .then((categoryData) => {
          const currentCategoryNotes = categoryData.docs.map((note) => {
            const noteData = note.data();
            return { ...noteData, id: note.id };
          });

          const currentCategoryData = category.data();

          return {
            id: category.id,
            name: currentCategoryData.name,
            notes: currentCategoryNotes,
          };
        });
    })
  ).then((categoryPromiseResults) => {
    let userData = {};

    categoryPromiseResults.forEach((category) => {
      userData[category.id] = {
        name: category.name,
        notes: category.notes,
      };
    });

    dispatch(notesDataFetch(userData));
    console.log('Extracting Notes Complete');
  });
};
