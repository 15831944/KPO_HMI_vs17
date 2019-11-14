/*
 * Erstellt mit SharpDevelop.
 * Benutzer: Christian
 * Datum: 03.04.2009
 * Zeit: 19:22
 */
using System;
using System.Collections.Generic;

namespace LibTelcom
{
	/// <summary>
	/// Description of Telegram.
	/// </summary>
	public class TelegramDefinition
	{
		private List<TelegramItem> _items;

    private string _description;
    public string Description
    {
      get
      {
        return _description;
      }
      set
      {
        _description = value;
      }
    }
		private string _telegramName;
		public string TelegramName
		{
			get
			{
				return _telegramName;
			}
		}
		public TelegramDefinition(string telegramName)
		{
			_telegramName = telegramName;
			_items = new List<TelegramItem>();
		}
		
		public override string ToString()
		{
			return _telegramName;
		}
		
		public List<TelegramItem> TelegramItems
		{
			get
			{
				return _items;
			}
		}
	}
}
