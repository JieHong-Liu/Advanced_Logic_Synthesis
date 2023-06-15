import csv

def writeToCSV(outputTXT,outputCSV):
    # Read the output file
    with open(outputTXT) as f:
        lines = f.readlines()

    # Define the headers for the CSV file
    headers = ['file', 'inputs', 'keys', 'outputs', 'gates', 'iteration', 'backbones_count', 'cube_count', 'cpu_time', 'maxrss', 'key']

    # Create a list to store the data for the CSV file
    data = []

    # Loop over each line in the output file
    for line in lines:
        # Split the line by spaces
        parts = line.split()
        print(parts)
        # If the line contains "Timeout", add None for each element and continue
        if "Timeout" in line:
            data.append([parts[3],'X','X','X','x','x','x','x','x'])
            continue

        # Extract the relevant information from the line
        file = parts[0]
        inputs = int(parts[1].split('=')[1])
        keys = int(parts[2].split('=')[1])
        outputs = int(parts[3].split('=')[1])
        gates = int(parts[4].split('=')[1])
        iteration = int(parts[5].split('=')[1].rstrip(';'))
        backbones_count = int(parts[6].split('=')[1].rstrip(';'))
        cube_count = int(parts[7].split('=')[1].rstrip(';'))
        cpu_time = float(parts[8].split('=')[1].rstrip(';'))
        maxrss = float(parts[9].split('=')[1].rstrip(';'))
        key = str(parts[10].split('=')[1])

        # Add the extracted information to the data list
        data.append([file, inputs, keys, outputs, gates, iteration, backbones_count, cube_count, cpu_time, maxrss, key])

    # Write the data to a CSV file
    with open(outputCSV, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(headers)
        writer.writerows(data)

    print("CSV file saved as ",outputCSV)

writeToCSV("sarlock-output.txt","sarlock-output.csv")
