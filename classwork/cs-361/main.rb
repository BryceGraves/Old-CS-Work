# Exercise 10

class LaunchDiscussionWorkflow

  def initialize(discussion, host, participants_email_string)
    @discussion = discussion
    @host = host
    @participants_email_string = participants_email_string
    @participants = []
  end

  # Expects @participants array to be filled with User objects
  def run
    run_callbacks(:create) do
      ActiveRecord::Base.transaction do
        discussion.save!
        create_discussion_roles!
        @successful = true
      end
    end
  end

  def generate_participant_users_from_email_string
    @participants_email_string.split.uniq.map do |email_address|
      User.create(email: email_address.downcase, password: Devise.friendly_token)
    end
  end

end

class ValidateDiscussionWorkflow
  def test_if_email_string_is_blank
    return if @participants_email_string.blank?
  end

  def is_valid
    return unless valid?
  end
end


discussion = Discussion.new(title: "fake", ...)
host = User.find(42)
participants = "fake1@example.com\nfake2@example.com\nfake3@example.com"

# Validation/Tests happens here...

workflow = LaunchDiscussionWorkflow.new(discussion, host, participants)
workflow.generate_participant_users_from_email_string
workflow.run

# Questions:
# 1. Although this course doesn't focus on testing, what does Uncle Bob's F.I.R.S.T acronym stand for? Tests should be...
#
# Fast
# Independent
# Repeatable
# Self Validating
# Timely
#
# 2. What is SRP (explain a little, don't just expand the acronym)?
#
# Each class should have one responsibility. We don't want classes with many jobs and many things to do.
#
# 3. The term "coupling" means that two things are dependent. What is cohesion, and how is it different from "coupling?"
#
# Cohesion: Classes that work together to accomplish something.
# Coupling: Classes that require eachother to work.
#
# 4. In Chapter 12, "Emergence" Jeff Langr summarizes Kent Beck's four rules of simple design. Briefly, what are the four rules?
#
# 1. Runs all test
# 2. Contains now duplicates
# 3. Expresses intent to the programmer
# 4. Minimize the number of classes and methods
