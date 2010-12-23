using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;
using System.IO;

namespace xml_test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Record the current time
            DateTime dateTime = DateTime.Now;

            // Create an array of boards
            Board[] Board = new Board[4];

            // Load data into the array
            Board[0] = new Board("Arduino Duemilanove", "arduino", "m328p", 57600, "flash:w:", "filename.hex",dateTime);
            Board[1] = new Board("Arduino Uno", "arduino", "m328p", 57600, "flash:w:", "filename.hex", dateTime);
            Board[2] = new Board("Butterfly", "butterfly", "m169", 19200, "flash:w:", "filename.hex", dateTime);
            Board[3] = new Board("BeAVR", "stk500", "m644p", 57600, "flash:w:", "filename.hex", dateTime);
                    
            using (System.Xml.XmlWriter writer = System.Xml.XmlWriter.Create("C:\\Temp\\Boards.xml"))
            {
                writer.WriteStartDocument();
                writer.WriteWhitespace("\n");
                writer.WriteStartElement("AVRIDE_Boards");
                writer.WriteWhitespace("\n");

                foreach (Board board in Board)
                {
                    writer.WriteStartElement("Board");
                    writer.WriteWhitespace("\n");

                    writer.WriteWhitespace("  ");
                    writer.WriteElementString("BoardName", board.BoardName.ToString());
                    writer.WriteWhitespace("\n");
                    writer.WriteWhitespace("  ");
                    writer.WriteElementString("Programmer", board.Programmer.ToString());
                    writer.WriteWhitespace("\n");
                    writer.WriteWhitespace("  ");
                    writer.WriteElementString("Part", board.Part.ToString());
                    writer.WriteWhitespace("\n");
                    writer.WriteWhitespace("  ");
                    writer.WriteElementString("Baudrate", board.Baudrate.ToString());
                    writer.WriteWhitespace("\n");
                    writer.WriteWhitespace("  ");
                    writer.WriteElementString("Memop", board.Memop.ToString());
                    writer.WriteWhitespace("\n");
                    writer.WriteWhitespace("  ");
                    writer.WriteElementString("DateTime", board.Now.ToString());                 
                    writer.WriteWhitespace("\n");  
                 
                    writer.WriteEndElement();
                    writer.WriteWhitespace(" \n");
                }

                writer.WriteEndElement();
                writer.WriteEndDocument();
                writer.Close();
            }


            }

        private void readBoard()
        {
// Create an XML reader for this file.
using (System.Xml.XmlReader reader = System.Xml.XmlReader.Create("C:\\Temp\\Board.xml"))
{
    // Skip over xml version stuff
    reader.MoveToContent();

    while (reader.Read())
    {
        if (reader.IsStartElement())
        {
            // Skip a line between each board
            if (reader.Name == "Board") richTextBoxXml.Text += "\n";
            else richTextBoxXml.Text += reader.Name + ": ";
        }
        if (reader.HasValue) richTextBoxXml.Text += reader.Value + "\n";
    }
}
        }

        private void button2_Click(object sender, EventArgs e)
        {
            readBoard();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("www.smileymicros.com");
        }        }

    // This is a test case for describing AVR development boards 
    // so that the descriptions can be used by avrdude.
    // The DateTime element was thrown in just to test different data types
    class Board
    {
        string _boardName;
        string _programmer;
        string _part;
        UInt32 _baudrate;
        string _memop;
        string _filename;
        DateTime _now;

        public Board(string boardName, string programmer, string part, UInt32 baudrate, string memop, string filename, DateTime now)
        {
            this._boardName = boardName;
            this._programmer = programmer;
            this._part = part;
            this._baudrate = baudrate;
            this._memop = memop;
            this._filename = filename;
            this._now = now;
        }

        public string BoardName {  get { return _boardName; } }
        public string Programmer { get { return  _programmer; } }
        public string Part { get { return _part;  } }
        public UInt32 Baudrate { get { return _baudrate; } }
        public string Memop { get { return _memop; } }
        public string Filename { get { return _filename; } }
        public DateTime Now { get { return _now; } }

    }

}
