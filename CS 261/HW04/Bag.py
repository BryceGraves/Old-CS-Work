from BstInterface import *

# The Bag Class
class Bag(object):

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):
        self._bst = newBSTree()

    #################################
    ## DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return whether or not the Bag is empty
    def is_empty(self):
        return isEmptyBSTree(self._bst) == 1

    # Return the size on the Bag
    def size(self):
        return sizeBSTree(self._bst)

    # return T/F whether or not the value is in the bag
    def contains(self, value):
        return containsBSTree(self._bst, value)

    # add a value to the bag
    def add(self, value):
        addBSTree(self._bst, value);

    # Remove a value from the bag
    def remove(self, value):
        removeBSTree(self._bst, value);

    #Iterators are coming! (traversals, actually...)

    def print_bag(self):
        ## NOTE: This actually just prints the tree, obviously
        # We need iterators to really print the bag (soon!)
        print "v"*150
        printTreeDepth(self._bst)
        print "^"*150
