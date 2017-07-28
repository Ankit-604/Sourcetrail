package com.sourcetrail.name;

import java.util.Optional;

public class JavaVariableDeclName extends JavaDeclName
{
	private JavaTypeName m_typeName = null;
	private boolean m_isStatic = false;
	
	public JavaVariableDeclName(String name, JavaTypeName typeName, boolean isStatic)
	{
		super(name);
		
		m_typeName = typeName;
		m_isStatic = isStatic;
	}
	
	@Override
	public NameHierarchy toNameHierarchy()
	{
		String prefix = "";
		if (m_isStatic)
		{
			prefix += "static ";
		}
		if (m_typeName != null)
		{
			prefix += m_typeName.toString();
		}
		
		NameHierarchy nameHierarchy = super.toNameHierarchy();
		Optional<NameElement> nameElement = nameHierarchy.peek();
		if (nameElement.isPresent())
		{
			String name = nameElement.get().getName();
			
			nameHierarchy.pop();
			nameHierarchy.push(new NameElement(name, prefix, ""));
		}
		return nameHierarchy;
	}
}