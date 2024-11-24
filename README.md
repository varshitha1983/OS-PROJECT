# Simplified Unix-Like Utilities

## Project Overview

This project involves the implementation of commonly used Unix-like utilities in C. Each utility replicates the functionality of corresponding Unix commands, offering valuable insights into system programming, file operations, and command-line interface design.

---

## File Structure
-

---
## Implemented Utilities

### 1. **Custom `ls`**
custom_ls [options] [path]
custom_ls               # List files in the current directory.
custom_ls -a            # Show hidden files.
custom_ls -l            # Recursively list files.
custom_ls -s            # Display files with their sizes in bytes.

### 2. **Custom `cat`**
custom_cat [-u|-l] file1 file2 ...
# Examples:
custom_cat file1.txt             # Display file contents.
custom_cat -u file1.txt          # Display contents in uppercase.
custom_cat file1.txt file2.txt   # Concatenate and display multiple files.

### 3. **Custom `grep`**
custom_grep [-i|-v] pattern file1 file2 ...
# Examples:
custom_grep "pattern" file1.txt        # Search for a pattern.
custom_grep -i "pattern" file1.txt     # Case-insensitive search.
custom_grep -v "pattern" file1.txt     # Display non-matching lines.

### 4. **Custom `wc`**
custom_wc file1 file2 ...
# Examples:
custom_wc file1.txt              # Count for a single file.
custom_wc file1.txt file2.txt    # Count for multiple files.

### 5. **Custom `cp`**
custom_cp [-r] source destination
# Examples:
custom_cp file1.txt file2.txt    # Copy file1.txt to file2.txt.
custom_cp -r dir1 dir2           # Copy dir1 to dir2 recursively.

### 6. **Custom `mv`**
custom_mv source destination
# Examples:
custom_mv old.txt new.txt        # Rename old.txt to new.txt.
custom_mv dir1 /path/to/dir2     # Move dir1 to a new location.

### 1. **Custom `rm`**
custom_rm [-r] file_or_directory
# Examples:
custom_rm file1.txt              # Delete file1.txt.
custom_rm -r dir1                # Recursively delete dir1.


