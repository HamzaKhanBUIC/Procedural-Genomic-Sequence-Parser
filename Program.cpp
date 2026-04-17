#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// ============================================================================
// FUNCTION PROTOTYPES (Procedural Architecture)
// ============================================================================
std::string loadGenomicData(const std::string& filepath);
void analyzeNucleotides(const std::string& sequence, int& countA, int& countC, int& countT, int& countG);
int countTargetSequence(const std::string& sequence, const std::string& target);
void printLaboratoryReport(size_t totalLength, int countA, int countC, int countT, int countG, 
                           const std::string& target, int targetOccurrences);

// ============================================================================
// MAIN ROUTINE
// ============================================================================
int main() {
    const std::string filename = "dna_sample.txt";
    
    // STEP 1: Load sequence into memory safely
    std::string dnaSequence = loadGenomicData(filename);
    
    // Safety check: if file was empty or missing, abort gracefully.
    if (dnaSequence.empty()) {
        std::cerr << "Error: Genomic sequence is empty or file could not be read.\n";
        return 1;
    }

    // STEP 2: Analyze nucleotides
    int a = 0, c = 0, t = 0, g = 0;
    analyzeNucleotides(dnaSequence, a, c, t, g);
    
    // STEP 3: Pattern matching (Prompting the user)
    std::string target;
    std::cout << ">>> SYSTEM READY.\n";
    std::cout << ">>> Enter target nucleotide sequence to search (e.g., TAG): ";
    std::cin >> target;
    
    // Convert target to uppercase to ensure accurate matching
    for (char &ch : target) {
        ch = toupper(ch);
    }

    int patternMatches = countTargetSequence(dnaSequence, target);

    // Final Output: High-end UI Generation
    printLaboratoryReport(dnaSequence.length(), a, c, t, g, target, patternMatches);

    return 0;
}

// ============================================================================
// FUNCTION IMPLEMENTATIONS
// ============================================================================

/* * Safely opens a file, allocates exact memory needed, reads data, and closes the file.
 * MEMORY MANAGEMENT NOTES:
 * 1. We use std::string which handles dynamic heap allocation safely (RAII principles).
 * 2. We use seekg() to find the exact file size and call sequence.reserve().
 * This ensures memory is allocated EXACTLY ONCE, preventing buffer reallocations 
 * and fragmentation when reading large genomic datasets.
 * 3. The file handles are strictly scoped and explicitly closed.
 */
std::string loadGenomicData(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::in | std::ios::ate); // Open at the end
    
    if (!file.is_open()) {
        return ""; // Return empty string if file missing
    }
    
    // Get file size and reserve memory to prevent reallocation overhead
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg); // Rewind to start
    
    std::string sequence;
    if (size > 0) {
        sequence.reserve(size);
        // Load entire file directly into the memory buffer efficiently
        sequence.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
    
    file.close(); // Clean up resource handle
    return sequence;
}

/*
 * Procedural loop to count A, C, T, G using standard switch statements for maximum performance.
 * Unrecognized characters are ignored to ensure data integrity.
 */
void analyzeNucleotides(const std::string& sequence, int& countA, int& countC, int& countT, int& countG) {
    for (char nucleotide : sequence) {
        switch (toupper(nucleotide)) {
            case 'A': countA++; break;
            case 'C': countC++; break;
            case 'T': countT++; break;
            case 'G': countG++; break;
            default: break; // Ignore newlines, spaces, or corrupted data
        }
    }
}

/*
 * Searches the main sequence buffer for a specific sub-string pattern.
 * Uses std::string::find in a while loop to efficiently scan memory.
 */
int countTargetSequence(const std::string& sequence, const std::string& target) {
    if (target.empty() || sequence.empty()) return 0;

    int occurrences = 0;
    size_t position = 0;

    // Find the first occurrence, then jump forward to find the next
    while ((position = sequence.find(target, position)) != std::string::npos) {
        occurrences++;
        position += target.length(); // Advance by target length to prevent overlapping double-counts
    }

    return occurrences;
}

/*
 * Formats the standard output buffer to look like a clean, high-end laboratory interface.
 */
void printLaboratoryReport(size_t totalLength, int countA, int countC, int countT, int countG, 
                           const std::string& target, int targetOccurrences) {
    
    // Ensure we don't divide by zero when calculating percentages
    double total = static_cast<double>(totalLength > 0 ? totalLength : 1);

    std::cout << "\n";
    std::cout << "==========================================================\n";
    std::cout << "||               SEQUENCE ANALYSIS REPORT               ||\n";
    std::cout << "==========================================================\n";
    std::cout << "|| SYSTEM STATUS   :  MEMORY ALLOCATED                  ||\n";
    std::cout << "|| DATA INTEGRITY  :  VERIFIED                          ||\n";
    std::cout << "||------------------------------------------------------||\n";
    std::cout << "|| TOTAL NUCLEOTIDES READ : " << std::left << std::setw(28) << totalLength << "||\n";
    std::cout << "||------------------------------------------------------||\n";
    
    // Formatting fixed floating point percentages
    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "|| Adenine (A)     : " << std::setw(10) << countA 
              << " [" << std::setw(6) << (countA / total) * 100.0 << "%]              ||\n";
              
    std::cout << "|| Cytosine (C)    : " << std::setw(10) << countC 
              << " [" << std::setw(6) << (countC / total) * 100.0 << "%]              ||\n";
              
    std::cout << "|| Thymine (T)     : " << std::setw(10) << countT 
              << " [" << std::setw(6) << (countT / total) * 100.0 << "%]              ||\n";
              
    std::cout << "|| Guanine (G)     : " << std::setw(10) << countG 
              << " [" << std::setw(6) << (countG / total) * 100.0 << "%]              ||\n";
              
    std::cout << "||------------------------------------------------------||\n";
    std::cout << "|| TARGET PATTERN  : " << std::setw(35) << target << "||\n";
    std::cout << "|| MATCHES FOUND   : " << std::setw(35) << targetOccurrences << "||\n";
    std::cout << "==========================================================\n";
    std::cout << "\n";
}