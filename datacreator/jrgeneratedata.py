import json



# Define the path to your text file
input_file_path = 'datacreator/coursedata.txt'

# Define the path to the output file
# We will then move the file to the database folder if we want
output_file_path = 'datacreator/createddata/'


# Read the file and process each line
course_data = []
with open(input_file_path, 'r') as file:
    for line in file:
        # Split the line into components
        parts = line.strip().split('\t') #
        
        
        course_dict = {
            "dept": parts[0],
            "course_number": int (parts[1]),
            "course_name": parts[2],
            "credits": int (parts[3]),
            "start_time": parts[4],
            "end_time": parts[5],
            "days": parts[6]
        }
        course_data.append(course_dict)
        
#Make sure to change the output file name here
with open(output_file_path + "CatalogData.json" , 'w') as json_file:
    json.dump(course_data, json_file, indent=4)

print("Course data converted to JSON successfully!")
