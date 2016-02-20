import tempfile
import zipfile

class WriteZipFile(object):
    """  
    Class that abstracts the handling of a zip file. The file is created by the constructor, then
    data is written by calling (one or multiple times) the 'write()' method, the content from the
    resulting zipped file can be read by calling (multiple times) the 'read()' method.
    """
    def __init__ (self):
        """ Constructor. No parameters accepted. It creates a temporary zip file in '/tmp'.
        """
        self.tmp_file = tempfile.TemporaryFile(mode="rw+b", dir="/tmp")
        self.zipper = zipfile.ZipFile(self.tmp_file, "w") 

    def write(self, arc_name, data):
        """
        Write data to the zip file. Invoking this method after calling the 'read()' method will
        raise an exception.
        @param data string to write.
        """
        self.zipper.writestr(arc_name, data)

    def read(self, size=1024):
        """
        Read data from the zip file.
        @param size number of bytes to read from the file. The default value is 1024 bytes.
        @return the string containing the bytes just read, or "" if there is nothing else to read.
        """
        if self.zipper is not None:
            self.zipper.close()
            self.tmp_file.seek(0)
        return self.tmp_file.read()

    def get_file_object(self):
        """ Return the zip file object already sought on byte zero. 
        """
        if self.zipper is not None:
            self.zipper.close()
            self.tmp_file.seek(0)
        return self.tmp_file


if __name__ == "__main__":
    zf = WriteZipFile()
    zf.write("test.log", "Test blabla")
    #bin_data = zf.read()
    fo = zf.get_file_object()
    print fo.read()
