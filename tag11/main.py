
import graphviz

# Read in file
with open('tag11/test_2.txt', 'r') as file:
    content = file.read()   

nodes = {}
for line in content.splitlines():
    line = line.strip()
    start, ends = line.split(": ")
    nodes[start] = ends.split(" ")

print(nodes)
f = graphviz.Digraph(filename='tag11/test_graph', format='png')
for start, ends in nodes.items():
    if start in ["svr", "fft", "dac", "out"]:
        f.node(start, fillcolor='red', style='filled')
    else:
        f.node(start)

for start, ends in nodes.items():
    for end in ends:
        f.edge(start, end)
f.render()