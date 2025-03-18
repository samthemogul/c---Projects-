#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <bitset>

void compressSegment(const std::string &input, std::vector<unsigned char> &output) {
    int n = input.length();
    int i = 0;

    while (i < n) {
        char currentChar = input[i];
        int count = 0;

        // Count consecutive characters
        while (i < n && input[i] == currentChar) {
            ++i;
            ++count;
        }

        // Append the character as a single byte (ASCII value)
        output.push_back(static_cast<unsigned char>(currentChar));

        // Append the count as a 2-byte unsigned integer
        output.push_back(static_cast<unsigned char>(count >> 8));  // High byte of count
        output.push_back(static_cast<unsigned char>(count & 0xFF));  // Low byte of count
    }
}

void decompressSegment(const std::vector<unsigned char> &input, std::string &output) {
    int n = input.size();
    int i = 0;

    while (i < n) {
        char currentChar = input[i];
        int count = (input[i + 1] << 8) | input[i + 2];

        // Append the character 'count' times
        for (int j = 0; j < count; ++j) {
            output.push_back(currentChar);
        }

        i += 3;
    }
}

int main() {
    std::string inputFile = "large_sequence.txt";
    std::string outputFile = "compressed_sequence.bin";
    std::string decompressedFile = "decompressed_sequence.txt";


    // Read input file
    std::ifstream inFile(inputFile, std::ios::in);
    if (!inFile) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return 1;
    }

    std::string inputContent;
    std::getline(inFile, inputContent, '\0');
    inFile.close();

    // Start timing the compression process
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<unsigned char> compressedContent;
    compressSegment(inputContent, compressedContent);
    

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Write compressed content to the output file (binary format)
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return 1;
    }

    outFile.write(reinterpret_cast<const char*>(compressedContent.data()), compressedContent.size());
    outFile.close();

    std::cout << "Compression completed. Compressed content written to " << outputFile << std::endl;
    std::cout << "Compression completed in " << elapsed.count() << " seconds." << std::endl;

    // Start timing the decompression process
    start = std::chrono::high_resolution_clock::now();

    std::string decompressedContent;
    decompressSegment(compressedContent, decompressedContent);

    // End timing
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;

    // Write decompressed content to the output file
    std::ofstream decompressedFileOut(decompressedFile, std::ios::out);
    if (!decompressedFileOut) {
        std::cerr << "Error: Could not open output file " << decompressedFile << std::endl;
        return 1;
    }

    decompressedFileOut << decompressedContent;
    decompressedFileOut.close();

    std::cout << "Deompression completed. Decompressed content written to " << decompressedFile << std::endl;
    std::cout << "Deompression completed in " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
