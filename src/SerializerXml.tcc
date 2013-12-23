
namespace rapid_parser
{

void SerializerXml::add( const char* key, const std::string& data, const std::vector< char* >& path )
{
	using namespace rapidxml;
	xml_node<>* v    = getValue( path );
	xml_node<>* node = doc.allocate_node( node_element, key, data.c_str() );
	
	if( v == nullptr )
		doc.append_node( node );
	else
		v->append_node( node );
	
}

void SerializerXml::add( const char* key, const size_t data, const std::vector< char* >& path )
{
	using namespace rapidxml;

	std::string str = std::to_string( data );
	
	char* d = doc.allocate_string( str.c_str() );
	memcpy( d, str.data(), str.size() );
	
	xml_node<>* v    = getValue( path );
	xml_node<>* node = doc.allocate_node( node_element, key, d );
	
	if( v == nullptr )
		doc.append_node( node );
	else
		v->append_node( node );
}

void SerializerXml::add( const char* key, const int data, const std::vector< char* >& path )
{
	using namespace rapidxml;
	std::string str = std::to_string( data );
	
	char* d = doc.allocate_string( str.c_str() );
	memcpy( d, str.data(), str.size() );

	xml_node<>* v    = getValue( path );
	xml_node<>* node = doc.allocate_node( node_element, key, d );
	
	if( v == nullptr )
		doc.append_node( node );
	else
		v->append_node( node );
}

void SerializerXml::add( const char* key, const double data, const std::vector< char* >& path )
{
	using namespace rapidxml;
	std::string str = std::to_string( data );
	
	char* d = doc.allocate_string( str.c_str() );
	memcpy( d, str.data(), str.size() );

	xml_node<>* v    = getValue( path );
	xml_node<>* node = doc.allocate_node( node_element, key, d );
	
	if( v == nullptr )
		doc.append_node( node );
	else
		v->append_node( node );
}

void SerializerXml::addEmptyElement( const std::vector< char* >& path )
{
	using namespace rapidxml;
	
	std::vector<char*> p;
	for( size_t index =0; index < path.size() - 1 ; ++index )
		p.push_back( path.at( index ) );
	
	xml_node<>* v = getValue( p );
	xml_node<>* newChild = doc.allocate_node( node_element, path.at( path.size() - 1 ) );
	
	v->append_node( newChild );
}

rapidxml::xml_node<>* SerializerXml::getValue( const std::vector< char* >& path )
{
	rapidxml::xml_node<>* v = nullptr;
	std::string fullPath;
	if( path.size() )
	{
		for( auto p : path )
		{
			fullPath += "/";
			fullPath += p;
			v = get( p, v );
		}
	}
	//std::cout << fullPath << std::endl;
	return v;
	return nullptr;
}

rapidxml::xml_node<>* SerializerXml::get( const char* id, rapidxml::xml_node<>* ref )
{
	using namespace rapidxml;
	if( ref == nullptr )
	{
		xml_node<>* n = doc.first_node( id );
		if( n )
		{
			return n;
		}
		else
		{
			xml_node<>* node = doc.allocate_node( node_element, id );
			doc.append_node( node );
			return node;
		}
	}
	else
	{
		xml_node<>* n = ref->last_node( id );
		if( n )
		{
			return n;
		}
		else
		{
			xml_node<>* node = doc.allocate_node( node_element, id );
			ref->append_node( node );
			return node;
		}
	}
	return nullptr;
}

}
