#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Running Norminette on so_long project files...${NC}"

# Check source files
echo -e "${BLUE}Checking source files...${NC}"
norminette src/*.c src/*.h 2>&1 | grep -v "mlx"

# Check header files in root directory
echo -e "${BLUE}Checking header files...${NC}"
norminette *.h 2>&1 | grep -v "mlx"

# Check any additional C files in root directory
echo -e "${BLUE}Checking C files in root directory...${NC}"
norminette *.c 2>&1 | grep -v "mlx"

echo -e "${GREEN}Norminette check completed!${NC}"