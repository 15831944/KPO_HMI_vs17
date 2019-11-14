/*
 * Erstellt mit SharpDevelop.
 * Benutzer: Christian
 * Datum: 03.04.2009
 * Zeit: 19:23
 */
using System;

namespace LibTelcom
{
	/// <summary>
	/// Description of TelegramItem.
	/// </summary>
	public class TelegramItem
	{
		public TelegramItem(string itemName, int index, int count, string comment, string dbCol)
		{
			_itemName = itemName;
			_count = count;
			_comment = comment;
            _index = index;
            _dbCol = dbCol;
		}
		
		private string _comment;
		public string Comment
		{
			get
			{
				return _comment;
			}
		}

        private int _index;
        public int Index
        {
            get { return _index; }
            set { _index = value; }
        }

        private string _dbCol;

        public string DatabaseColumn
        {
            get { return _dbCol; }
            set { _dbCol = value; }
        }
		
		private int _count;
		public int Count
		{
			get
			{
				return _count;
			}
		}
		
		private string _itemName;
		public string Name
		{
			get
			{
				return _itemName;
			}
		}
	}
}
