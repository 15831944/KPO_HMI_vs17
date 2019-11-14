/*
 * Erstellt mit SharpDevelop.
 * Benutzer: Christian
 * Datum: 03.04.2009
 * Zeit: 19:25
 */
using System;
using System.Collections.Generic;

namespace LibTelcom
{
	/// <summary>
	/// Description of UserDefinedItem.
	/// </summary>
	public class UserDefinedItem : TelegramItem
	{
		private List<TelegramItem> _items;
		
		public List<TelegramItem> SubItems
		{
			get
			{
				return _items;
			}
		}
		
		private string _userDefinedTypeName;
		
		public string UserDefinedTypeName {
			get { return _userDefinedTypeName; }
		}
		
		public UserDefinedItem(string itemName, int count, int index, string comment, string userDefinedTypeName, string dbCol) : base(itemName, index, count, comment, dbCol)
		{
			_userDefinedTypeName = userDefinedTypeName;
			_items = new List<TelegramItem>();
		}
	}
}
