﻿using System;
using System.Windows.Input;

namespace Novah.Tracer.Server
{
    public class RelayCommand : ICommand
    {
        private readonly Action<object> _execute;
        private readonly Predicate<object> _predicate;

        public RelayCommand(Action<object> execute, Predicate<object> predicate = null)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");

            _execute = execute;
            _predicate = predicate;
        }

        public void Execute(object parameter)
        {
            _execute(parameter);
        }

        public bool CanExecute(object parameter)
        {
            return _predicate == null ? true : _predicate(parameter);
        }

        public event EventHandler CanExecuteChanged
        {
            add
            {
                CommandManager.RequerySuggested += value;
            }
            remove
            {
                CommandManager.RequerySuggested -= value;
            }
        }
    }
}