""" $ python createPartitions.py node.json edge.txt numPartitions """
import sys
import os


def main():
	nodeFile = sys.argv[1]
	edgeFile = sys.argv[2]
	numPartitions = int(sys.argv[3])

	fin = open(edgeFile, "r")

	n = 1
	m = 0
	mapping = {}
	
	adjacencyList = [[]]

	for line in fin:
		line = line.strip().split()
		x = int(line[0])
		y = int(line[1])

		if x not in mapping:
			mapping[x] = n
			adjacencyList.append([])
			n+=1

		if y not in mapping:
			mapping[y] = n
			adjacencyList.append([])
			n+=1

		adjacencyList[mapping[x]].append(mapping[y])
		adjacencyList[mapping[y]].append(mapping[x])

		m+=1

	fin.close()

	adjacencyFile = "adjacency.txt"
	fout = open(adjacencyFile, "w")

	fout.write(str(n-1) + " " + str(m) + "\n")
	for i in range(1, len(adjacencyList)):
		for j in adjacencyList[i]:
			fout.write(str(j) + " ")
		fout.write("\n")

	fout.close()



	## Execute gpmetis
	os.system("gpmetis " + adjacencyFile + " " + str(numPartitions))

	partitionMap = {}
	fin = open(adjacencyFile+".part."+str(numPartitions), "r")
	i = 1
	for line in fin:
		metisPartitionId = int(line.strip())
		partitionMap[i] = metisPartitionId
		i+=1

	fin.close()

	partitionNodeFileNames = []
	for i in range(numPartitions):
		partitionNodeFileNames.append("nodepartition"+str(i))
		open("nodepartition"+str(i), "w").close() #Clear files



	partitionEdgeFileNames = []
	for i in range(numPartitions):
		partitionEdgeFileNames.append("edgepartition"+str(i))
		open("edgepartition"+str(i), "w").close()


	fin = open(nodeFile, "r")
	for line in fin:
		originalLine = line
		line = line.strip().split()
		nodeId = int(line[0])
		# nodeJson = line[1]

		mappedNodeId = mapping[nodeId]
		partition = partitionMap[mappedNodeId]

		with open(partitionNodeFileNames[partition], "a") as fout:
			fout.write(originalLine)

	fin.close()

	fin = open(edgeFile, "r")
	for line in fin:
		line = line.strip().split()
		x = int(line[0])
		y = int(line[1])
		
		mappedNodeIdX = mapping[x]
		partitionX = partitionMap[mappedNodeIdX]

		mappedNodeIdY = mapping[y]
		partitionY = partitionMap[mappedNodeIdY]

		with open(partitionEdgeFileNames[partitionX], "a") as fout:
			fout.write(str(x) + " " + str(y) + " " + str(partitionY) + "\n")

		with open(partitionEdgeFileNames[partitionY], "a") as fout:
			fout.write(str(y) + " " + str(x) + " " + str(partitionX) + "\n")

	fin.close()






if __name__ == "__main__":
	main()