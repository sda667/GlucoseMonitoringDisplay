import pandas as pd
import matplotlib.pyplot as plt 

# Replace with the actual path to your CSV file
file_path = 'C:/Users/JohnDoe/Downloads/glucose_24-10-2012.csv'

# Read the CSV file into a pandas DataFrame
data = pd.read_csv(file_path, header=1)

# Convert the 'Device Timestamp' column to datetime format
data['Device Timestamp'] = pd.to_datetime(data['Device Timestamp'], format='%d/%m/%Y %H:%M')

# Print the minimum and maximum timestamps in the data
print("Min Device Timestamp:", data['Device Timestamp'].min())
print("Max Device Timestamp:", data['Device Timestamp'].max())

# Calculate the timestamp 24 hours ago from the maximum timestamp in the data
twenty_four_hours_ago = data['Device Timestamp'].max() - pd.DateOffset(hours=24)

# Print the calculated timestamp 8 hours ago
print("Device Timestamp 24 Hours Ago:", twenty_four_hours_ago)

# Select rows where the 'Device Timestamp' is within the last 24 hours
selected_data = data[data['Device Timestamp'] >= twenty_four_hours_ago]

sel_gluc_mg = selected_data['Historic Glucose mmol/L']*18

# Display the selected data or perform further analysis
print(selected_data)

# Find the row with the maximum timestamp (latest entry)
latest_entry = data.loc[data['Device Timestamp'].idxmax()]

# Extract relevant information (replace with actual column names)
historic_glucose_value = latest_entry['Historic Glucose mmol/L']
scan_glucose_value = latest_entry['Scan Glucose mmol/L']
timestamp = latest_entry['Device Timestamp']

# Check if historic glucose data is available and not NaN, otherwise use scan glucose data
if pd.notna(historic_glucose_value) and not pd.isna(historic_glucose_value):
    glucose_value = historic_glucose_value
else:
    glucose_value = scan_glucose_value if pd.notna(scan_glucose_value) else "Data Not Available"

# Print the latest glucose data
print("Latest Glucose Data:")
print(f"Glucose: {glucose_value} mmol/L")
print(f"Timestamp: {timestamp}")

# Save the latest glucose data to a text file
latest_glucose_data = f"Latest Glucose Data:\nGlucose: {glucose_value} mmol/L\nTimestamp: {timestamp}"
with open('latest_glucose_data.txt', 'w') as file:
    file.write(latest_glucose_data)

fig = plt.figure()
ax = fig.add_subplot(111)
green = sel_gluc_mg.mask(data["Historic Glucose mmol/L"]*18 > 120)
red = sel_gluc_mg.mask(data["Historic Glucose mmol/L"]*18 <= 120)
ax.plot(selected_data['Device Timestamp'], sel_gluc_mg, color='y')
ax.plot(selected_data['Device Timestamp'], red, color='r')
ax.plot(selected_data['Device Timestamp'], green, color='g')

plt.ylabel('Glucose (mg/dl)')
plt.xlabel('Time (heures)')
ax.xaxis.set_ticklabels(['-24', '-21', '-18', '-15', '-12', '-9', '-6', '-3', 'NOW'])
plt.savefig('graph.png')
plt.show()
print(data.columns)
