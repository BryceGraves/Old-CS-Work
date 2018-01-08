from DynamicArray import DynamicArray

# The Stack Class
# Python has all kinds of powerful stuff that does what your Stack needs to do
# No, you CAN'T use any of that
# You need to use your Dynamic Array implementation instead


class Stack(object):

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):
        self._size = 0
        self._dynamic_array = DynamicArray()

    #################################
    # DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return the size of the dynamic array
    def is_empty(self):
        # TODO: return True or False to answer if the stack is empty
        if self._size == 0:
            return True

    # Return the capacity of the dynamic array
    def size(self):
        # TODO: return the current size of the stack
        return self._size

    # Add an element to the end of the dynamic array
    def top(self):
        # TODO: return the current top of the stack
        return self._dynamic_array.get(self._size - 1)

    # Get the value at the position passed in as a parameter
    def push(self, value):
        # TODO: push the passed value onto the stack
        self._dynamic_array.add(value)
        self._size += 1

    # Put a value into the dynamic array at the specified position
    def pop(self):
        # TODO: pop the top value off the stack
        self._dynamic_array.remove(self._size - 1)
        self._size -= 1

    # DO NOT MODIFY THIS PRINT
    def print_stack(self):
        print '====\n' + '\n----\n'.join([str(v) for v in self._dynamic_array._data[:self._size]]) + '\n^^^^'