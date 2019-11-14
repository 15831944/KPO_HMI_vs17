/*
 * Erstellt mit SharpDevelop.
 * Benutzer: Christian
 * Datum: 03.04.2009
 * Zeit: 19:24
 */
using System;

namespace LibTelcom
{
	/// <summary>
	/// Description of PrimitiveItem.
	/// </summary>
	public class PrimitiveItem : TelegramItem
	{
        public PrimitiveItem(string itemName, int count, int index, string comment, int fieldLength, TelcomDataType type, string unit, string minVal, string maxVal, string dbCol)
            : base(itemName, index, count, comment, dbCol)
		{
			_fieldLength = fieldLength;
			_dataType = type;
            _unit = unit;
            _minVal = minVal;
            _maxVal = maxVal;
		}

        private string _minVal;

        public string MinVal
        {
            get { return _minVal; }
            set { _minVal = value; }
        }
        private string _maxVal;

        public string MaxVal
        {
            get { return _maxVal; }
            set { _maxVal = value; }
        }

        private string _unit;
        public string Unit
        {
            get { return _unit; }
            set { _unit = value; }
        }
		
		private TelcomDataType _dataType;
		public TelcomDataType DataType 
		{
			get
			{ 
				return _dataType; 
			}
		}
		private int _fieldLength;
		public int FieldLength
		{
			get
			{
				return _fieldLength;
			}
		}
	}
}
