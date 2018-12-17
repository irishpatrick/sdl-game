namespace engine 
{
    template <class T>
    void Group::getSpritesByType(std::vector<T*>& vec)
	{
        for (auto& e : renderList)
		{
            if (T* type = dynamic_cast<T*>(e))
			{
                vec.push_back(type);
            }
        }
    }
}
