using System;
using System.Collections.Generic;
using System.Text;

using System.Reflection;
using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    public class XmlSerializerCache
    {
        private List<XmlSerializerCacheItem> cache = new List<XmlSerializerCacheItem>();

        public XmlSerializerCache()
        {
        }

        public void cacheAssemblyTypes(Assembly _assembly)
        {
            try
            {
                if (_assembly != null)
                {
                    Type[] assemblyTypeList = _assembly.GetTypes();

                    foreach (Type curType in assemblyTypeList)
                    {
                        addCache(curType);
                    }
                }
            }
            catch
            {
            }
        }

        public void cacheAssemblyTypes(String _assemblyFile)
        {
            try
            {
                cacheAssemblyTypes(Assembly.LoadFrom(_assemblyFile));
            }
            catch
            {
            }
        }

        public XmlSerializerCacheItem addCache(Type _objectType)
        {
            if (!_objectType.IsSubclassOf(typeof(XmlSerializable)))
            {
                return null;
            }

            XmlSerializerCacheItem cacheItem = cache.Find(
                delegate(XmlSerializerCacheItem _cacheItem)
                {
                    return _cacheItem.TypeName == _objectType.Namespace + "." + _objectType.Name;
                }
            );

            if (cacheItem == null)
            {
                cacheItem = new XmlSerializerCacheItem(_objectType.Namespace + "." + _objectType.Name, new XmlSerializer(_objectType));
                cache.Add(cacheItem);
            }

            return cacheItem;
        }

        public XmlSerializer getSerializer(Type _objectType)
        {
            XmlSerializerCacheItem cacheItem = addCache(_objectType);

            return (cacheItem == null) ? null : cacheItem.XmlSerializer;
        }
    }
}
