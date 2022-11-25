#########################################################################################
# Here you need to write some basic tests to make sure your Queue implementation runs correctly
# You can run them by running 'python QueueTests.py' from the command line
#########################################################################################

from Queue import Queue

queue = Queue()

print "Checking basic variable initializations..."

queue.add_back(1);
queue.add_back(2);
queue.add_back(3);
queue.add_back(4);

queue.print_queue()
print "done\n"

###################################

print "Checking is_empty and size..."

assert queue.size() == 4;
assert queue.is_empty() == False;

queue.print_queue();
print "done\n"

###################################

print "Checking front, removeFront..."
print queue.front()
print "\n"

queue.print_queue();

print "\n"

queue.removeFront();

queue.print_queue();
print "done\n"

###################################

print "Checking back, addBack..."
print queue.back();
print "\n"

queue.print_queue()

print "\n"

queue.add_back(42);
queue.print_queue()
print "done\n"

###################################

queue.print_queue()
print "All checks passed"
