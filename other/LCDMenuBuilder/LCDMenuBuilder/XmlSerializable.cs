using System;
using System.Collections.Generic;
using System.Text;

using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace LCDMenuBuilder
{
    /// <summary>
    /// Default XML serializer
    /// </summary>
    public abstract class XmlSerializable
    {
        /// <summary>
        /// XMLSerializer cache
        /// </summary>        
        public static XmlSerializerCache GlobalSerializerCache = new XmlSerializerCache();

        private XmlReaderSettings readerSettings = null;
        private XmlWriterSettings writerSettings = null;

        public XmlSerializable()
        {
        }

        [XmlIgnore]
        public XmlReaderSettings ReaderSettings
        {
            get
            {
                if (readerSettings == null)
                {
                    readerSettings = new XmlReaderSettings();
                    readerSettings.IgnoreComments = true;
                    readerSettings.IgnoreWhitespace = true;
                }

                return readerSettings;
            }

            set
            {
                readerSettings = value;
            }
        }

        [XmlIgnore]
        public XmlWriterSettings WriterSettings
        {
            get
            {
                if (writerSettings == null)
                {
                    writerSettings = new XmlWriterSettings();
                    writerSettings.OmitXmlDeclaration = true;
                    writerSettings.Indent = true;
                }

                return writerSettings;
            }

            set
            {
                writerSettings = value;
            }
        }

        /// <summary>
        /// Serialize object
        /// </summary>
        /// <param name="_stream">Stream</param>
        public virtual void serialize(Stream _stream)
        {
            GlobalSerializerCache.getSerializer(this.GetType()).Serialize(XmlWriter.Create(_stream, WriterSettings),
                this,
                new XmlSerializerNamespaces
                (
                    new XmlQualifiedName[]
                    {
                        new XmlQualifiedName(String.Empty)
                    }
                )
            );
        }

        public virtual void serialize(XmlWriter _xmlWriter)
        {
            GlobalSerializerCache.getSerializer(this.GetType()).Serialize(_xmlWriter,
                this,
                new XmlSerializerNamespaces
                (
                    new XmlQualifiedName[]
                    {
                        new XmlQualifiedName(String.Empty)
                    }
                )
            );
        }

        public virtual void serialize(String _filePath)
        {
            String dirPath = Path.GetDirectoryName(_filePath);
            if (!Directory.Exists(dirPath))
            {
                Directory.CreateDirectory(dirPath);
            }

            using (FileStream curFileStream = File.Create(_filePath))
            {
                serialize(curFileStream);
                curFileStream.Close();
            }
        }

        /// <summary>
        /// Copy current object in other type
        /// </summary>
        /// <returns>New objct instance</returns>
        public virtual object copyTo(Type _targetObjectType)
        {
            MemoryStream stream = new MemoryStream();
            serialize(stream);
            stream.Seek(0, SeekOrigin.Begin);

            return XmlSerializable.deserialize(stream, _targetObjectType);
        }

        /// <summary>
        /// Copy current object
        /// </summary>
        /// <returns>New objct instance</returns>
        public object copy()
        {
            return copyTo(this.GetType());
        }

        /// <summary>
        /// Deserialize object
        /// </summary>
        /// <param name="_stream">Stream</param>
        /// <param name="_xmlSerializer">Cached serializer</param>
        /// <returns>Deserialized object</returns>
        public static object deserialize(Stream _stream, XmlSerializer _xmlSerializer)
        {
            XmlReaderSettings readerSettings = new XmlReaderSettings();
            readerSettings.IgnoreComments = true;
            readerSettings.IgnoreWhitespace = true;

            return _xmlSerializer.Deserialize(XmlReader.Create(_stream, readerSettings));
        }

        /// <summary>
        /// Deserialize object
        /// </summary>
        /// <param name="_stream">Stream</param>
        /// <param name="_objectType">Type of deserializable object</param>
        /// <returns>Deserialized object</returns>
        public static object deserialize(Stream _stream, Type _objectType)
        {
            return XmlSerializable.deserialize(_stream, GlobalSerializerCache.getSerializer(_objectType));
        }

        public static object deserialize(XmlReader _xmlReader, XmlSerializer _xmlSerializer)
        {
            return _xmlSerializer.Deserialize(_xmlReader);
        }

        public static object deserialize(XmlReader _xmlReader, Type _objectType)
        {
            return XmlSerializable.deserialize(_xmlReader, GlobalSerializerCache.getSerializer(_objectType));
        }

        public static object deserialize(String _filePath, Type _objectType)
        {
            object curObject = null;

            using (FileStream curFileStream = File.OpenRead(_filePath))
            {
                curObject = deserialize(curFileStream, _objectType);
                curFileStream.Close();
            }

            return curObject;
        }

        public static object deserialize(String _filePath, XmlSerializer _xmlSerializer)
        {
            object curObject = null;

            using (FileStream curFileStream = File.OpenRead(_filePath))
            {
                deserialize(curFileStream, _xmlSerializer);
                curFileStream.Close();
            }

            return curObject;
        }
    }
}
