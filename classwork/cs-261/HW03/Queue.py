from LinkedListInterface import *

# The Queue Class
# Python has all kinds of powerful stuff that does what your Queue needs to do
# No, you CAN'T use any of that
# You need to use your Linked List implementation instead

class Queue(object):

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):
        self._linked_list = createLinkedList()

    #################################
    ## DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return whether or not the queue is empty
    def is_empty(self):
        return isEmptyList(self._linked_list) == 1

    # Return the size on the queue
    def size(self):
        return self._linked_list.contents.size

    # THIS IS COMMENTED OUT SINCE YOU'RE ONLY IMPLEMENTING THE QUEUE
    # # add a value to the front of the queue
    # def addFront(self):
    #     #TODO: add a value to the front of the queue
    #     return 1

    # remove a value from the front of the queue
    def removeFront(self):
        removeFrontList(self._linked_list);

    # return the front (first) value in the queue
    def front(self):
        return frontList(self._linked_list)

    # add a value to the back of the queue
    def add_back(self, val):
        addBackList(self._linked_list, val);

    # THIS IS COMMENTED OUT SINCE YOU'RE ONLY IMPLEMENTING THE QUEUE
    # # remove a value from the back of the queue
    # def removeBack(self):
    #     # TODO: remove a value from the back of the queue
    #     return 1

    # return the back (last) value in the queue
    def back(self):
        return backList(self._linked_list)

    # DO NOT MODIFY THIS PRINT
    def print_queue(self):
        printList(self._linked_list);
