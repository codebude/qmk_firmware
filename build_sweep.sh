#!/bin/bash


# Create a temporary file to store the output
TMP_FILE=$(mktemp)
# Run the qmk compile command, capture its output and print it in real-time
qmk compile -km rh_colemak | tee "$TMP_FILE"
# Extract the filename from the last line of the output
BUILD_FILE=$(tail -n 1 "$TMP_FILE" | awk '{print $2}')
echo "Build file: $BUILD_FILE"

echo -e "\nPlease set keyboard to bootloader mode (double-tap reset button) now."
echo -n "Please enter drive letter (default=d): "

# Read the user input
read DRIVE_LETTER

# Check if the user entered a value
if [ -z "$DRIVE_LETTER" ]; then
  # If no input was given, set DRIVE_LETTER to "d"
  DRIVE_LETTER="d"
fi
# Output the value of DRIVE_LETTER
echo "Drive letter set to: $DRIVE_LETTER"

# Mount USB drive
MNT_PATH="/mnt/$DRIVE_LETTER"
sudo mkdir -p $MNT_PATH
sudo mount -t drvfs $DRIVE_LETTER: $MNT_PATH -o uid=$(id -u $USER),gid=$(id -g $USER),metadata
cp $BUILD_FILE $MNT_PATH
sudo umount $MNT_PATH
sudo rm -r $MNT_PATH