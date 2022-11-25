class CreateSpaces < ActiveRecord::Migration[5.2]
  def change
    create_table :spaces do |t|
      t.string :space_type
      t.integer :destination
      t.references :game
      
      t.timestamps
    end
  end
end
