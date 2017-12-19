open Utils;

open Types;

type state = list(item);

type action =
  | AddItem(string)
  | ToggleItem(int)
  | StartEditingItem(int)
  | FinishEditingItem(int, string);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (~text as title) => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false, editing: false}
};

let reducer = (action, items) =>
  switch action {
  | AddItem(text) => ReasonReact.Update([newItem(~text), ...items])
  | ToggleItem(id) =>
    ReasonReact.Update(
      List.map((item) => item.id === id ? {...item, completed: ! item.completed} : item, items)
    )
  | StartEditingItem(id) =>
    Js.log("start editing item " ++ string_of_int(id));
    ReasonReact.Update(
      List.map(
        (item) => item.id === id ? {...item, editing: true} : {...item, editing: false},
        items
      )
    )
  | FinishEditingItem(id, text) =>
    Js.log("finish editing item " ++ string_of_int(id) ++ " " ++ text);
    ReasonReact.Update(
      List.map((item) => item.id === id ? {...item, editing: false, title: text} : item, items)
    )
  };

let make = (_) => {
  ...component,
  initialState: () => [],
  reducer,
  render: ({state: items, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do?"))
        <div className="add-todo">
          <AddTodoField onSubmit=(reduce((text) => AddItem(text))) />
        </div>
      </div>
      <div className="items">
        (
          List.map(
            (item) =>
              <TodoItem
                key=(string_of_int(item.id))
                onToggle=(reduce(() => ToggleItem(item.id)))
                onEditStart=(reduce(() => StartEditingItem(item.id)))
                onEditDone=((text) => reduce(() => FinishEditingItem(item.id, text), ()))
                item
              />,
            items
          )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="footer"> (getFormattedNumberOfItems(numItems)) </div>
    </div>
  }
};