#include "stdafx.h"
#include "K_MeansClusterAlgorithm.h"


K_MeansClusterAlgorithm::K_MeansClusterAlgorithm(unsigned int k) : Algorithm("K_Means_Cluster_"), k(k)
{
	if (k >= 100) {
		std::cout << "Cluster size k too big, picking standart size 3.";
		this->k = 3;
	}
}


K_MeansClusterAlgorithm::~K_MeansClusterAlgorithm()
{
}

void K_MeansClusterAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	srand(time(NULL));
	int * redClusters = new int[k];
	int * greenClusters = new int[k];
	int * blueClusters = new int[k];
	unsigned int i;
	for (i = 0; i < k; i++) {
		int x, y;
		x = (int)((double)rand() / (double)RAND_MAX * (double)width);
		y = (int)((double)rand() / (double)RAND_MAX * (double)height);
		int pixel = y * pitch + x * bpp;
		redClusters[i] = rawData[pixel + RED];
		greenClusters[i] = rawData[pixel + GREEN];
		blueClusters[i] = rawData[pixel + BLUE];
	}
	int * redClusterTotal = new int [k];
	int * greenClusterTotal = new int [k];
	int * blueClusterTotal = new int [k];
	int * clusterCount = new int[k];
	unsigned int x, y, closest, cluster, distClosest, distCluster;
	for (i = 0; i < 25; i++) {
		std::cout << "Iteration " << i + 1 << "\n";
		for (cluster = 0; cluster < k; cluster++) {
			redClusterTotal[cluster] = 0;
			greenClusterTotal[cluster] = 0;
			blueClusterTotal[cluster] = 0;
			clusterCount[cluster] = 0;
		}
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