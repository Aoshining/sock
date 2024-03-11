function add() {
	var username=document.getElementById("input1").value;
	var comment=document.getElementById("input2").value;
	if(username!==""&&comment!=="")
	{
		var parent=document.createElement("div");
		parent.classList.add("comment");

		var out1=document.createElement("h3");
		out1.textContent=username;
		parent.appendChild(out1);

		var out2=document.createElement("p");
		out2.textContent=comment;
		parent.appendChild(out2);

		var but=document.createElement("button");
		but.textContent="删除";
		but.onclick=function(){del(parent)};
		parent.appendChild(but);
		
		
		document.getElementById("output").appendChild(parent);
		document.getElementById("input1").value="";
		document.getElementById("input2").value="";
	}
}

function del(parent){
	parent.remove();
}