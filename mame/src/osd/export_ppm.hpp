#pragma once

#include <iostream>
#include <fstream>
#include <string>
typedef struct RGB {
	unsigned char r, g, b;
} rgb;

class ExportPPM
{
public:
	static void exportPPM(const std::string& filename, const unsigned char* data, int width, int height, const unsigned char* palette, const unsigned char* ctable)
	{
		std::cout << "Exporting to PPM file: " << filename << std::endl;

		std::ofstream file(filename, std::ios::binary);
		file << "P3\n" << width << " " << height << "\n255\n";

		for (int i = 0; i < width * height; i++) {

			int m = data[i];
			int c = ctable[m];

			//std::cout << " " << std::to_string(c);

			const rgb palette_default[4] = {
				{ 0, 0, 0 },
				{ 85, 85, 85 },
				{ 170, 170, 170 },
				{ 255, 255, 255 }
			};

			if (palette == nullptr) {
				file << (" " + std::to_string(palette_default[c].r));
				file << (" " + std::to_string(palette_default[c].g));
				file << (" " + std::to_string(palette_default[c].b));
			}
			else {
				file << (" " + std::to_string(palette[3 * c + 0]));
				file << (" " + std::to_string(palette[3 * c + 1]));
				file << (" " + std::to_string(palette[3 * c + 2]));
			}

			if ((i % width) == 0) {
				file.put('\n');
				std::cout << std::endl;
			}	
		}
		file.close();
	}
};
