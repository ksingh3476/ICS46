// Digraph.hpp
//
// ICS 46 Spring 2017
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException
{
public:
    DigraphException(const std::string& reason): reason_{reason} { }

    std::string reason() const { return reason_; }

private:
    std::string reason_;
};



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a template
// struct.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a template struct.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d);

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph();

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d);

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.
    std::map<int,DigraphVertex<VertexInfo,EdgeInfo>> info;
    //bool areVerticiesConnected(int vertexFrom, int VertexTo, std::map<int, bool>& visited) const;
    bool checkConnectivity(int from,std::vector<int> visited) const;
    inline int findMinimum(const std::vector<int>& vertices, const std::map<int, double> &shortDistances) const; 
    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};


// You'll need to define the member functions of your Digraph class
// template here.
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::Digraph() 
{
    
}
       
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::Digraph(const Digraph& d)
{
    this->info = d.info;
}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::Digraph(Digraph&& d)
{
    this->info.swap(d.info);     
}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::~Digraph()
{
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::iterator iter=info.begin();iter!=info.end();iter++)
    {
        iter->second.edges.clear();
    }
    info.clear();
}

template <typename VertexInfo, typename EdgeInfo>  
Digraph<VertexInfo,EdgeInfo>& Digraph<VertexInfo,EdgeInfo>::operator=(const Digraph& d)
{
    this->info = d.info;
    return *this;
}

template<typename VertexInfo, typename EdgeInfo>   
Digraph<VertexInfo,EdgeInfo>& Digraph<VertexInfo,EdgeInfo>::operator=(Digraph&& d)
{
    this->info.swap(d.info);
    return *this;
}

template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo,EdgeInfo>::vertices() const
{
    std::vector<int> result;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator it=info.begin();it!=info.end();it++)
        result.push_back(it->first);
    return result; 
}

template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo,EdgeInfo>::edges() const
{
    std::vector<std::pair<int,int>> result;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iter=info.begin();iter!=info.end();iter++)
    {
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator it = iter->second.edges.begin();it!=iter->second.edges.end();it++)
            result.push_back(std::make_pair(it->fromVertex,it->toVertex));
    }
    return result;
}

template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo,EdgeInfo>::edges(int vertex) const
{
    if(info.count(vertex)==0)
    {
        throw DigraphException("Invalid vertex");
    }
    else 
    {
        std::vector<std::pair<int,int>> result;
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator it=info.find(vertex)->second.edges.begin();it!=info.find(vertex)->second.edges.end();it++)
            result.push_back(std::make_pair(vertex,it->toVertex));
        return result;
    }
}

template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo,EdgeInfo>::vertexInfo(int vertex) const
{
    if(info.count(vertex)==0)
        throw DigraphException("Invalid vertex");
    else
        return info.at(vertex).vinfo;
}

template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo,EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if(info.count(fromVertex)==0 || info.count(toVertex)==0)
        throw DigraphException("Invalid edge");
    else
    {
        std::vector<std::pair<int,int>> temp = edges(fromVertex);
        std::pair<int,int> check = std::make_pair(fromVertex,toVertex);
        if(std::find(temp.begin(),temp.end(),check)==temp.end())
            throw DigraphException("Invalid edge");
    }
    for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator it=info.at(fromVertex).edges.begin();it!=info.at(fromVertex).edges.end();it++)
    {
        if(it->toVertex==toVertex)
            return it->einfo;
    }
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if(info.count(vertex)!=0)
        throw DigraphException("Vertex already exists");
    DigraphVertex<VertexInfo,EdgeInfo> v = DigraphVertex<VertexInfo,EdgeInfo>{vinfo};
    info.insert(std::pair<int,DigraphVertex<VertexInfo,EdgeInfo>>(vertex,v));
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if(info.count(fromVertex)==0 || info.count(toVertex)==0)
        throw DigraphException("Invalid edge");
    else
    {
        std::vector<std::pair<int,int>> temp = edges(fromVertex);
        std::pair<int,int> check = std::make_pair(fromVertex,toVertex);
        if(std::find(temp.begin(),temp.end(),check)!=temp.end())    
            throw DigraphException("Invalid edge");
    }
    info.at(fromVertex).edges.push_back(DigraphEdge<EdgeInfo>{fromVertex,toVertex,einfo});
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::removeVertex(int vertex)
{
    if(info.count(vertex)==0)
        throw DigraphException("Invalid vertex");
    info.erase(vertex);
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::iterator iter=info.begin();iter!=info.end();iter++)
    {
        typename std::list<DigraphEdge<EdgeInfo>>::iterator it= iter->second.edges.begin();   
        while(it!=iter->second.edges.end())
        {
            if(it->toVertex == vertex)
                iter->second.edges.erase(it);
            it++;
        }
    }
    info.erase(vertex);
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    if(info.count(fromVertex)==0 || info.count(toVertex)==0)
        throw DigraphException("Invalid edge");
    else
    {
        std::vector<std::pair<int,int>> temp = edges(fromVertex);
        std::pair<int,int> check = std::make_pair(fromVertex,toVertex);
        if(std::find(temp.begin(),temp.end(),check)==temp.end())
            throw DigraphException("Invalid edge");
    }
    typename std::list<DigraphEdge<EdgeInfo>>::iterator it=info.at(fromVertex).edges.begin();   
    while(it!=info.at(fromVertex).edges.end())
    {
        if(it->toVertex == toVertex)
             info.at(fromVertex).edges.erase(it);
           it++;
    }
}

template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo,EdgeInfo>::vertexCount() const
{
    return info.size();
}

template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo,EdgeInfo>::edgeCount() const
{
    int total;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iter=info.begin();iter!=info.end();iter++)
        total += iter->second.edges.size();
    return total;
}

template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo,EdgeInfo>::edgeCount(int vertex) const
{
    if(info.count(vertex)==0)
        throw DigraphException("Invalid vertex");
    return info.at(vertex).edges.size();
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo,EdgeInfo>::checkConnectivity(int from,std::vector<int> visited) const
{
    std::vector<int> vertice = vertices();
    for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator it = info.at(from).edges.begin();it!=info.at(from).edges.end();it++)
    {
        if(std::find(visited.begin(),visited.end(),it->toVertex)==visited.end())
            visited.push_back(it->toVertex);
        else if(visited.size() < vertice.size()-1)
            checkConnectivity(it->toVertex,visited);
        else
            return true;
    }
    return false;
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iter=info.begin();iter!=info.end();iter++)
    {
        std::vector<int> visited;
        if(!checkConnectivity(iter->first,visited))
            return false;
    }
    return true; 
}

template <typename VertexInfo, typename EdgeInfo>
inline int Digraph<VertexInfo,EdgeInfo>::findMinimum(const std::vector<int>& vertices, const std::map<int, double> &shortestDist) const 
{
    double minVal = 8000000000000;
    int minVert;
    
    for(int i=0;i<vertices.size();i++)
    {
        if(shortestDist.at(vertices[i]) < minVal)
        {
           minVal = shortestDist.at(vertices[i]);
           minVert = vertices[i];
        }  
    }
    return minVert;
}

template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{   
    
    std::map<int, double> shortestDist;
    std::vector<int> unvisited;
    std::map<int, int> shortestPath;
    
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iter=info.begin();iter!=info.end();iter++)
    {
        unvisited.push_back(iter->first);
        shortestDist[iter->first] = 80000000000000;
    }
    
    shortestDist[startVertex] = 0;
    shortestPath[startVertex] = startVertex;
    
    
    while(!unvisited.empty())
    {
        int current = findMinimum(unvisited, shortestDist);
        for (int i=0;i<unvisited.size();i++)
        {
            if (unvisited[i] == current)
            {
                unvisited.erase(unvisited.begin()+i);
                break;
            }
        }
        
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator it=info.at(current).edges.begin();it!=info.at(current).edges.end();it++)
        {
            double distance = shortestDist[current] + edgeWeightFunc(it->einfo);
            if(distance < shortestDist[it->toVertex])
            {
                shortestDist[it->toVertex]= distance;
                shortestPath[it->toVertex] = current;
            }
        }
    }
    
    return shortestPath;
    
}


#endif // DIGRAPH_HPP

