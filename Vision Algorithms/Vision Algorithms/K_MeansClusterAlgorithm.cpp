#include "stdafx.h"
#include "K_MeansClusterAlgorithm.h"


K_MeansClusterAlgorithm::K_MeansClusterAlgorithm(unsigned int k) : Algorithm("_Means_Cluster_"), k(k)
{
	if (k >= 100) {
		std::cout << "Cluster size k too big, picking standart size 3.";
		this->k = 3;
	}

	char * newName = (char*)malloc(sizeof(char*)* 20);

	newName[0] = '0' + (char)(this->k / 10);
	newName[1] = '0' + (char)(this->k % 10);
	int i;
	for (i = 0; i < 17; i++) {
		newName[i + 2] = name[i];
	}
	newName[i] = '\0';
	name = newName;
}


K_MeansClusterAlgorithm::~K_MeansClusterAlgorithm()
{
}

void K_MeansClusterAlgorithm::doAlgorithm(Image& img) {
	srand(time(NULL));
	//setup
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	int * redClusters = new int[k];
	int * greenClusters = new int[k];
	int * blueClusters = new int[k];
	unsigned int i;
	//picking k random pixels
	//pixels can be picked twice but with the iterations this is no problem
	for (i = 0; i < k; i++) {
		int x, y;
		x = (int)((double)rand() / (double)RAND_MAX * (double)width);
		y = (int)((double)rand() / (double)RAND_MAX * (double)height);
		int pixel = y * pitch + x * bpp;
		redClusters[i] = rawData[pixel + RED];
		greenClusters[i] = rawData[pixel + GREEN];
		blueClusters[i] = rawData[pixel + BLUE];
	}
	//initializing data for each cluster
	int * redClusterTotal = new int [k];
	int * greenClusterTotal = new int [k];
	int * blueClusterTotal = new int [k];
	int * clusterCount = new int[k];
	unsigned int x, y, closest, cluster, distClosest, distCluster;
	for (i = 0; i < 25; i++) {
		//reset clusters
		std::cout << "Iteration " << i + 1 << "\n";
		for (cluster = 0; cluster < k; cluster++) {
			redClusterTotal[cluster] = 0;
			greenClusterTotal[cluster] = 0;
			blueClusterTotal[cluster] = 0;
			clusterCount[cluster] = 0;
		}
		//walk through each pixel and determine the closest cluster
		for (y = 0; y < height; y++) {
			for (x = 0; x < pitch; x += bpp) {
				int pixel = y * pitch + x;
				closest = 0;
				distClosest = (rawData[pixel + RED] - redClusters[closest]) * (rawData[pixel + RED] - redClusters[closest])
							+ (rawData[pixel + GREEN] - greenClusters[closest]) * (rawData[pixel + GREEN] - greenClusters[closest])
							+ (rawData[pixel + BLUE] - blueClusters[closest]) * (rawData[pixel + BLUE] - blueClusters[closest]);
				for (cluster = 0; cluster < k; cluster++) {
					distCluster = (rawData[pixel + RED] - redClusters[cluster]) * (rawData[pixel + RED] - redClusters[cluster])
								+ (rawData[pixel + GREEN] - greenClusters[cluster]) * (rawData[pixel + GREEN] - greenClusters[cluster])
								+ (rawData[pixel + BLUE] - blueClusters[cluster]) * (rawData[pixel + BLUE] - blueClusters[cluster]);
					if (distClosest > distCluster) {
						closest = cluster;
						distClosest = distCluster;
					}
				}
				redClusterTotal[closest] += rawData[pixel + RED];
				greenClusterTotal[closest] += rawData[pixel + GREEN];
				blueClusterTotal[closest] += rawData[pixel + BLUE];
				clusterCount[closest]++;
			}
		}
		//Update the clusters and check if they have changed
		int unchangedClusters = 0;
		for (cluster = 0; cluster < k; cluster++) {
			if (clusterCount[cluster] != 0) {
				if (redClusters[cluster] == (redClusterTotal[cluster] / clusterCount[cluster]) &&
					greenClusters[cluster] == (greenClusterTotal[cluster] / clusterCount[cluster]) &&
					blueClusters[cluster] == (blueClusterTotal[cluster] / clusterCount[cluster])) {
						unchangedClusters++;
				}
				else {
					redClusters[cluster] = (redClusterTotal[cluster] / clusterCount[cluster]);
					greenClusters[cluster] = (greenClusterTotal[cluster] / clusterCount[cluster]);
					blueClusters[cluster] = (blueClusterTotal[cluster] / clusterCount[cluster]);
				}
			}
			else {
				unchangedClusters++;
			}
		}
		if (unchangedClusters == k) break;
	}
	//change the picture according to the clusters
	std::cout << "Starting picture change\n";
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			int pixel = y * pitch + x;
			closest = 0;
			distClosest = (rawData[pixel + RED] - redClusters[closest]) * (rawData[pixel + RED] - redClusters[closest])
						+ (rawData[pixel + GREEN] - greenClusters[closest]) * (rawData[pixel + GREEN] - greenClusters[closest])
						+ (rawData[pixel + BLUE] - blueClusters[closest]) * (rawData[pixel + BLUE] - blueClusters[closest]);
			for (cluster = 0; cluster < k; cluster++) {
				distCluster = (rawData[pixel + RED] - redClusters[cluster]) * (rawData[pixel + RED] - redClusters[cluster])
					+ (rawData[pixel + GREEN] - greenClusters[cluster]) * (rawData[pixel + GREEN] - greenClusters[cluster])
					+ (rawData[pixel + BLUE] - blueClusters[cluster]) * (rawData[pixel + BLUE] - blueClusters[cluster]);
				if (distClosest > distCluster) {
					closest = cluster;
					distClosest = distClosest;
				}
			}
			rawData[y * pitch + x + RED] = redClusters[closest];
			rawData[y * pitch + x + GREEN] = greenClusters[closest];
			rawData[y * pitch + x + BLUE] = blueClusters[closest];
		}
	}
}