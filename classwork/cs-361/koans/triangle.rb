# Triangle Project Code.

# Triangle analyzes the lengths of the sides of a triangle
# (represented by a, b and c) and returns the type of triangle.
#
# It returns:
#   :equilateral  if all sides are equal
#   :isosceles    if exactly 2 sides are equal
#   :scalene      if no sides are equal
#
# The tests for this method can be found in
#   about_triangle_project.rb
# and
#   about_triangle_project_2.rb
#
def triangle(a, b, c)
  if a <=0 or c <=0 or c <=0
    raise TriangleError, "Sides of a triangle cannot be less or equal to zero."
  elsif(((a + b) <= c) or ((a + c) <= b) or ((b + c) <= a))
    raise TriangleError, "Two sides must add to be more than the third side."
  end

  #Check for triangle after sure one can exist
  if a == b and b == c and a == c
    :equilateral
  elsif a == b and b != c
    :isosceles
  elsif a == c and c != b
    :isosceles
  elsif b == c and c != a
    :isosceles
  else
    :scalene
  end
end

# Error class used in part 2.  No need to change this code.
class TriangleError < StandardError
end
